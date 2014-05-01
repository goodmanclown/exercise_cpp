#include "PrintCharacter.hxx"

#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <thread>
#include <vector>

using namespace std;

void* start_thread(void* arg)
{
	if (NULL == arg) return NULL;

	// cast the arg back to the object
	PrintCharacter& pc = *((PrintCharacter*)arg);

	// find the unique characters
	pc.run();

	return NULL;
}


PrintCharacter::PrintCharacter():mOutChar(0),mShutdown(false),mTid(-1) 
{
	// create the attribute to explicitly set joinable 
	pthread_attr_init(&mAttr);
	pthread_attr_setdetachstate(&mAttr, PTHREAD_CREATE_JOINABLE);

	size_t stacksize;
	pthread_attr_getstacksize(&mAttr, &stacksize);
	pid_t tid = (pid_t) syscall (SYS_gettid);
	cout << tid << " stack size " << stacksize << endl;

	// create the attribute to explicitly set errocheck 
	pthread_mutexattr_init(&mMutexAttr);
	pthread_mutexattr_settype(&mMutexAttr, PTHREAD_MUTEX_ERRORCHECK);

	// create the mutex
	pthread_mutex_init(&mMutex, &mMutexAttr);

	// create conditional variable
	pthread_cond_init(&mCondRead, NULL);

	// create conditional variable
	pthread_cond_init(&mCondWrite, NULL);
}


PrintCharacter::~PrintCharacter() 
{
	// lock the mutex
	pthread_mutex_lock(&mMutex);

	mShutdown = true;

	// signal read thread
	pthread_cond_signal(&mCondRead);

	// unlock the mutex
	pthread_mutex_unlock(&mMutex);

	if (mTid != -1) {
		// wait for the read thread to join
		int* status = NULL;
		pthread_join(mTid, (void**)&status);

		pid_t tid = (pid_t) syscall (SYS_gettid);
		cout << tid << " thread exit " << *status << endl;
		delete status;
	}

	// destroy the attribute
	pthread_attr_destroy(&mAttr);

	// destroy the conditional variable
	pthread_cond_destroy(&mCondWrite);

	// destroy the conditional variable
	pthread_cond_destroy(&mCondRead);

	// destroy the mutex
	pthread_mutex_destroy(&mMutex);
}


void PrintCharacter::start()
{
	// start the read thread
	pthread_create(&mTid, &mAttr, start_thread, this);
}


void PrintCharacter::stop() 
{
	// lock the mutex
	pthread_mutex_lock(&mMutex);

	mShutdown = true;

	// signal read thread
	pthread_cond_signal(&mCondRead);

	// unlock the mutex
	pthread_mutex_unlock(&mMutex);
}


void PrintCharacter::run()
{

	pid_t tid = (pid_t) syscall (SYS_gettid);

	// lock the mutex
	pthread_mutex_lock(&mMutex);

	cout << tid << " in run" << mShutdown << " " << mOutChar << endl;

	while (mShutdown == false && mOutChar == 0) {

		cout << tid << " wait for something" << endl;

		// wait for either shutdown or a character
		pthread_cond_wait(&mCondRead, &mMutex);

		// cout << "got the signal" << endl;

		if (mShutdown == false && mOutChar != 0) {
			// print the character
			cout << tid << " read mOutChar=" << mOutChar << endl;
			// cout << mOutChar;
			
			// clear the character
			mOutChar = 0;

			// signal the write thread
			pthread_cond_signal(&mCondWrite);
		}
	}

	// unlock the mutex
	pthread_mutex_unlock(&mMutex);

	// new an int to pass back the status
	// int* status = new int(-1);
	// pthread_exit(status);
}


void PrintCharacter::write(char outChar)
{
	pid_t tid = (pid_t) syscall (SYS_gettid);
	int ret = pthread_mutex_lock(&mMutex);
	cout << tid << " lock ret " << ret << endl;

	// write the input
	mOutChar = outChar;

	// cout << "write mOutChar=" << mOutChar << endl;

	// signal the read thread
	pthread_cond_signal(&mCondRead);

	// wait for the read thread to pick up the character
	// mutex must remain lock for this call to block
	pthread_cond_wait(&mCondWrite, &mMutex);

	// ret = pthread_mutex_lock(&mMutex);
	// cout << tid << " lock ret " << ret << endl;

	// after return, mutex is locked again
	// unlock the mutex
	pthread_mutex_unlock(&mMutex);
}


void PrintCharacter::process(uint32_t numOfThreads, const char inputString[], uint32_t lenOfInputString)
{
  	cout << "start" << endl;   

	if (!numOfThreads) return;

	if (!lenOfInputString) return;

	// create an array of PrintCharacter objects
	PrintCharacter** pcList = new PrintCharacter*[numOfThreads];

	// create a vector of thread
	vector<thread> threadVector;
	threadVector.clear();

	// populate the array
	for (uint32_t index=0; index < numOfThreads; index++) {
		
		// create the objects
		pcList[index] = new PrintCharacter();

		// start the objects
		threadVector.push_back(thread(&PrintCharacter::run, pcList[index]));
	}

	// wait a sec for the thread to startup
	sleep(1);

	// now go through the input string array 1 by 1
	for (uint32_t index=0; index < lenOfInputString; index++) {
		char inChar = inputString[index];

		// find the next pc object to use
		// use a mod will circulate through the list of pc objects
		int pcindex = index % numOfThreads;

		// cout << "index=" << index << ", pcindex=" << pcindex << endl;
 
		PrintCharacter* pc = pcList[pcindex];

		pc->write(inChar);
	}

	// print the new line
	cout << endl;

	// after finishing with the writing, free the objects
	for (uint32_t index=0; index < numOfThreads; index++) {
		// delete the objects
		delete pcList[index];
	}

	// join the threads
	for (auto& th : threadVector) {
		th.join();
	}

	// delete the list
	delete [] pcList;

	cout << "done" << endl; 

}


void PrintCharacter::processNonStdThread(uint32_t numOfThreads, const char inputString[], uint32_t lenOfInputString)
{
  	cout << "start" << endl;   

	if (!numOfThreads) return;

	if (!lenOfInputString) return;

	// create an array of PrintCharacter objects
	PrintCharacter** pcList = new PrintCharacter*[numOfThreads];

	// populate the array
	for (uint32_t index=0; index < numOfThreads; index++) {
		// create the objects
		pcList[index] = new PrintCharacter();

		// start the objects
		pcList[index]->start();

	}

	// wait a sec for the thread to startup
	sleep(1);

	// now go through the input string array 1 by 1
	for (uint32_t index=0; index < lenOfInputString; index++) {
		char inChar = inputString[index];

		// find the next pc object to use
		// use a mod will circulate through the list of pc objects
		int pcindex = index % numOfThreads;

		// cout << "index=" << index << ", pcindex=" << pcindex << endl;
 
		PrintCharacter* pc = pcList[pcindex];

		pc->write(inChar);
	}

	// print the new line
	cout << endl;

	// after finishing with the writing, free the objects
	for (uint32_t index=0; index < numOfThreads; index++) {
		// delete the objects
		delete pcList[index];
	}

	// delete the list
	delete [] pcList;

	cout << "done" << endl; 

}

