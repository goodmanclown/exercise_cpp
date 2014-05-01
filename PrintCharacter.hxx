#include <pthread.h>
#include <stdint.h>

/**
 * class to print character using thread synchronization
 */ 
class PrintCharacter {

public:

	/** 
    * Constructor
	 */
	PrintCharacter();


	/** 
    * Destructor
	 */
	~PrintCharacter();


	/**
	 * @param numOfThreads - number of threads
	 * @param inputString - an array of character to be printed
	 * @param lenOfInputString - length of the input array
	 */
	static void process(uint32_t numOfThreads, const char inputString[], uint32_t lenOfInputString);


	/**
	 * @param numOfThreads - number of threads
	 * @param inputString - an array of character to be printed
	 * @param lenOfInputString - length of the input array
	 */
	static void processNonStdThread(uint32_t numOfThreads, const char inputString[], uint32_t lenOfInputString);


	/**
	 * start the read thread
    */
	void start();


	/**
	 * run the read thread
    */
	void run();


	/**
	 * stop the read thread
    */
	void stop();


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
	 * a conditional mutex to notify read thread
	 */
	pthread_cond_t		mCondRead;


	/**
	 * a conditional mutex to notify write thread
	 */
	pthread_cond_t		mCondWrite;


	/**
    * a mutex to protect mOutputCharacter
	 */
	pthread_mutex_t	mMutex;


	/**
	 * a mutex attr
	 */
	pthread_mutexattr_t		mMutexAttr;


	/**
	 * character to be printed
	 */
	char					mOutChar;


	/**
	 * true if shutdown read thread
	 */
	bool			mShutdown;
	

	/**
	 * read thread tid
	 */
	pthread_t			mTid;
	
};


