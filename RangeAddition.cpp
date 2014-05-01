#include "RangeAddition.hxx"

#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>

using namespace std;

void* start_thread(void* arg)
{
	if (NULL == arg) return NULL;

	// cast the arg back to the object
	RangeAddition& pc = *((RangeAddition*)arg);

	// calculate the sum 
	pc.run();

	return NULL;
}


RangeAddition::RangeAddition(const Range& range):mRange(range),mTid(-1) 
{
	// create the attribute to explicitly set joinable 
	pthread_attr_init(&mAttr);
	pthread_attr_setdetachstate(&mAttr, PTHREAD_CREATE_JOINABLE);

	size_t stacksize;
	pthread_attr_getstacksize(&mAttr, &stacksize);
	pid_t tid = (pid_t) syscall (SYS_gettid);
	cout << tid << " stack size " << stacksize << endl;
}


RangeAddition::~RangeAddition() 
{
	// destroy the attribute
	pthread_attr_destroy(&mAttr);
}


void RangeAddition::join()
{
	// wait for the run thread to join
	int* sum = NULL;

	// the result is passed back as join status
	pthread_join(mTid, (void**)&sum);

	pid_t tid = (pid_t) syscall (SYS_gettid);
	cout << tid << " from " << mRange.mBegin << " to " << mRange.mEnd << " sum " << *sum << endl;
	delete sum;

}


void RangeAddition::start()
{
	// start the read thread
	pthread_create(&mTid, &mAttr, start_thread, this);
}


void RangeAddition::run()
{

	pid_t tid = (pid_t) syscall (SYS_gettid);

	cout << tid << " run" << endl;

	// (n(n+1) - m(m-1))/2
	uInt sum = (mRange.mEnd*(mRange.mEnd+1) - mRange.mBegin*(mRange.mBegin-1)) / 2; 

	// new an int to pass back the result
	int* status = new int(sum);
	pthread_exit(status);
}




void RangeAddition::process(uInt numOfThreads, const Range inputRange[])
{
  	cout << "start" << endl;   

	if (!numOfThreads) return;

	// create an array of RangeAddition objects
	RangeAddition** pcList = new RangeAddition*[numOfThreads];

	// populate the array
	for (int index=0; index < numOfThreads; index++) {
		// create the objects, with the input range
		pcList[index] = new RangeAddition(inputRange[index]);

		// start the objects
		pcList[index]->start();

	}


	// after finishing with the startup, join the threads
	for (int index=0; index < numOfThreads; index++) {
		// join the threads
		pcList[index]->join();
	}

	// after finishing with the addition, free the objects
	for (int index=0; index < numOfThreads; index++) {
		// delete the objects
		delete pcList[index];
	}

	// delete the list
	delete [] pcList;

	cout << "done" << endl; 

}

