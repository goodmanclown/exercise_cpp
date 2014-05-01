#include "Scheduler.hxx"

#include <memory>
#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>

using namespace std;

void* start_thread(void* arg)
{
	if (NULL == arg) return NULL;

	// cast the arg back to the object
	Scheduler& pc = *((Scheduler*)arg);

	// get the next job to be exeuted
	pc.run();

	return NULL;
}


Scheduler::Scheduler():MutexSingLinkedList(),mShutdown(false),mTid(0) 
{
	// create the attribute to explicitly set joinable 
	pthread_attr_init(&mAttr);
	pthread_attr_setdetachstate(&mAttr, PTHREAD_CREATE_JOINABLE);

	size_t stacksize;
	pthread_attr_getstacksize(&mAttr, &stacksize);
	pid_t tid = (pid_t) syscall (SYS_gettid);
	cout << tid << " stack size " << stacksize << endl;

	// create the attribute to explicitly set errocheck 
   pthread_mutexattr_t mtxAttr;
	pthread_mutexattr_init(&mtxAttr);
	pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_ERRORCHECK);

	// create the mutex
	pthread_mutex_init(&mMutex, &mtxAttr);

	// create conditional variable
	pthread_cond_init(&mCondRead, NULL);
}


Scheduler::~Scheduler() 
{
	mShutdown = true;

	{
		// lock the mutex for predictable scheduling policy
		// lock the mutex
		Lock l(mMutex);

		// signal read thread
		pthread_cond_signal(&mCondRead);
	
		// unlock the mutex
	}

	// wait for the read thread to join
	if (mTid > 0) {
		int* status = NULL;
		pthread_join(mTid, (void**)&status);

		pid_t tid = (pid_t) syscall (SYS_gettid);
		if (status) cout << tid << " thread exit " << *status << endl;
		delete status;
	}

	// destroy the attribute
	pthread_attr_destroy(&mAttr);

	// destroy the conditional variable
	pthread_cond_destroy(&mCondRead);

	// destroy the mutex
	pthread_mutex_destroy(&mMutex);
}


void Scheduler::start()
{
	// start the read thread
	pthread_create(&mTid, &mAttr, start_thread, this);

	sleep(1);
}


void Scheduler::run()
{
	pid_t tid = (pid_t) syscall (SYS_gettid);

	try {
		cout << tid << " in run" << endl;

		while (false == mShutdown) {


			// lock the mutex
			Lock l(mMutex);

			cout << tid << " wait for something" << endl;

			// wait for a job or a shutdown
			pthread_cond_wait(&mCondRead, &mMutex);

			cout << tid << " got the signal" << endl;

			if (false == mShutdown) {
				// not a signal to shutdown
				while (0 != getLength()) {
					// loop to retrieve all jobs from the list before returning to wait for more

					// wrap the pop job in an auto_ptr to make sure it gets deleted
					auto_ptr<SchedulerJob> job(dynamic_cast<SchedulerJobPtr>(pop_front()));

					if (NULL != job.get()) {
						cout << tid << " job " << *job << endl;
					}
				}
			}
			// unlock the mutex
		}
	}
	catch (exception& err) {
		// new an int to pass back the status
		int* status = new int(-1);
		pthread_exit(status);
	}

	// new an int to pass back the status
	int* status = new int(0);
	pthread_exit(status);
}


bool Scheduler::add(uint32_t priority, uint32_t id)
{
	try {

		SchedulerJobPtr job = new (nothrow) SchedulerJob(priority, id);

		if (NULL == job) return false;

		// queue the job
		bool ret = insert(job);

		if (true == ret && 1 == getLength()) {
			// signal the read thread about this new job, if this is the only job in the list 
			// if not the only job, read thread is already in a loop to pop jobs from the queue
			// no need to signal
			// 
			// read thread will get this signal next time it got a chance to run 
			// lock the mutex for predictable scheduling policy
			Lock l(mMutex);
			pthread_cond_signal(&mCondRead);

			// unlock the mutex
		}

		return ret;
	}
	catch (exception& err) {
		return false;
	}
}


