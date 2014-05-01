#include "SemaPrintCharacter.hxx"

#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

using namespace std;

void* start_thread(void* arg)
{
	if (NULL == arg) return NULL;

	// cast the arg back to the object
	SemaPrintCharacter& pc = *((SemaPrintCharacter*)arg);

	// find the unique characters
	pc.run();

	return NULL;
}


SemaPrintCharacter::SemaPrintCharacter():mOutChar(0),mShutdown(false),mTid((pthread_t)-1) 
{
	pid_t tid = (pid_t) syscall (SYS_gettid);

	// create sema read
   // pshared = 0 - shared between threads of the same process
   // value = 0 - initial value of the semaphore.  with value only between 0 and 1, this is a binary sema
	int ret = sem_init(&mSemRead, 0, 0);
	if (ret != 0) cout << tid << " errno " << errno << endl;

	// create sema write
	ret = sem_init(&mSemWrite, 0, 0);
	if (ret != 0) cout << tid << " errno " << errno << endl;
}


SemaPrintCharacter::~SemaPrintCharacter() 
{
	mShutdown = true;

	// signal read thread
	sem_post(&mSemRead);

	// wait for the read thread to join
	int* status = NULL;
	pthread_join(mTid, (void**)&status);

	pid_t tid = (pid_t) syscall (SYS_gettid);
	cout << tid << " thread exit " << *status << endl;
	delete status;

	// destroy the attribute
	pthread_attr_destroy(&mAttr);

	// destroy the sema 
	sem_destroy(&mSemWrite);

	// destroy the sema 
	sem_destroy(&mSemRead);

}


void SemaPrintCharacter::start()
{
	// create the attribute to explicitly set joinable 
	pthread_attr_init(&mAttr);
	pthread_attr_setdetachstate(&mAttr, PTHREAD_CREATE_JOINABLE);

	size_t stacksize;
	pthread_attr_getstacksize(&mAttr, &stacksize);
	pid_t tid = (pid_t) syscall (SYS_gettid);
	cout << tid << " stack size " << stacksize << endl;

	// start the read thread
	pthread_create(&mTid, &mAttr, start_thread, this);
}


void SemaPrintCharacter::run()
{
	pid_t tid = (pid_t) syscall (SYS_gettid);

	cout << "in run" << endl;

	int ret = 0;
	while ((ret = sem_wait(&mSemRead)) == 0 && false == mShutdown)  {
	
		cout << "got the signal" << endl;

		if (mOutChar != 0) {
			// print the character
			cout << tid << " read mOutChar=" << mOutChar << endl;
			
			// clear the character
			mOutChar = 0;

			// signal the write thread
			sem_post(&mSemWrite);
		}
	}

	// new an int to pass back the status
	int* status;
	if (ret != 0) status = new int(errno);
	else status = new int(0);
	pthread_exit(status);
}


void SemaPrintCharacter::write(char outChar)
{
	pid_t tid = (pid_t) syscall (SYS_gettid);

	// write the input
	mOutChar = outChar;

	cout << tid << " write mOutChar=" << mOutChar << endl;

	// signal the read thread
	int ret = sem_post(&mSemRead);
	if (ret != 0) cout << tid << " errno " << errno << endl;

	// wait for the read thread to pick up the character
	ret = sem_wait(&mSemWrite);
	if (ret != 0) cout << tid << " errno " << errno << endl;
}


void SemaPrintCharacter::process(uint32_t numOfThreads, const char inputString[], uint32_t lenOfInputString)
{
  	cout << "start" << endl;   

	if (!numOfThreads) return;

	if (!lenOfInputString) return;

	// create an array of SemaPrintCharacter objects
	SemaPrintCharacter** pcList = new SemaPrintCharacter*[numOfThreads];

	// populate the array
	for (int index=0; index < numOfThreads; index++) {
		// create the objects
		pcList[index] = new SemaPrintCharacter();

		// start the objects
		pcList[index]->start();

	}

	// wait a sec for the thread to startup
	sleep(1);

	// now go through the input string array 1 by 1
	for (int index=0; index < lenOfInputString; index++) {
		char inChar = inputString[index];

		// find the next pc object to use
		// use a mod will circulate through the list of pc objects
		int pcindex = index % numOfThreads;

		// cout << "index=" << index << ", pcindex=" << pcindex << endl;
 
		SemaPrintCharacter* pc = pcList[pcindex];

		pc->write(inChar);
	}

	// print the new line
	cout << endl;

	// after finishing with the writing, free the objects
	for (int index=0; index < numOfThreads; index++) {
		// delete the objects
		delete pcList[index];
	}

	// delete the list
	delete [] pcList;

	cout << "done" << endl; 

}

