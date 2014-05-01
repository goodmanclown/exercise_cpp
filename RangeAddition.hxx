#include <pthread.h>


/**
 * class to print character using thread synchronization
 */ 
class RangeAddition {

public:

	typedef unsigned int uInt;

	typedef struct _range {
		uInt mBegin;
		uInt mEnd;
	} Range;


	/** 
    * Constructor
	 */
	RangeAddition(const Range& range);


	/** 
    * Destructor
	 */
	~RangeAddition();


	/**
	 * @param numOfThreads - number of threads
	 * @param inputRange - an array of Range to be calculated. number of elements is same of number of threads
	 */
	static void process(uInt numOfThreads, const Range inputRange[]);


	/**
	 * start the run thread
    */
	void start();


	/**
	 * join the run thread
    */
	void join();


	/**
	 * run the read thread
    */
	void run();



private:


	/**
	 * a thread attr
	 */
	pthread_attr_t		mAttr;


	/**
	 * character to be printed
	 */
	Range					mRange;


	/**
	 * read thread tid
	 */
	pthread_t			mTid;
	
};


