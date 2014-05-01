#include <pthread.h>
#include <semaphore.h>

#include <stdint.h>


/**
 * class to print character using thread synchronization with semaphore
 */ 
class SemaPrintCharacter {

public:


	/** 
    * Constructor
	 */
	SemaPrintCharacter();


	/** 
    * Destructor
	 */
	~SemaPrintCharacter();


	/**
	 * @param numOfThreads - number of threads
	 * @param inputString - an array of character to be printed
	 * @param lenOfInputString - length of the input array
	 */
	static void process(uint32_t numOfThreads, const char inputString[], uint32_t lenOfInputString);


	/**
	 * start the read thread
    */
	void start();


	/**
	 * run the read thread
    */
	void run();


	/**
	 * @param outChar - character to be written
	 */
	void write(char outChar);


private:


	/**
	 * a thread attr
	 */
	pthread_attr_t		mAttr;


	/**
	 * a sema to notify read thread
	 */
	sem_t		mSemRead;


	/**
	 * a sema to notify write thread
	 */
	sem_t		mSemWrite;


	/**
	 * character to be printed
	 */
	char					mOutChar;


	/**
	 * true if shutdown read thread
	 */
	bool					mShutdown;
	

	/**
	 * read thread tid
	 */
	pthread_t			mTid;
	
};


