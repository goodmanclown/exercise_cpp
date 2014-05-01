#include "MutexSingLinkedList.hxx"
#include "SchedulerJob.hxx"

#include <stdint.h>
#include <pthread.h>
#include <stdexcept>
#include <atomic>


using std::runtime_error;
using std::atomic_bool;

/**
 * class to implement a scheduler
 *
 * this is implemented as a link list, instead of queue, is to allow jobs with different prioprities to 
 * be put into the same container.
 * if a queue is provided for each priority, ArrayQueue will be more appropriate.
 */
class Scheduler : public MutexSingLinkedList {

public:

	/** 
    * Constructor
	 */
	Scheduler();


	/** 
    * Destructor
	 */
	~Scheduler();


	/**
	 * start the read thread
    */
	void start();


	/**
	 * run the read thread
    */
	void run();


	/**
	 * @param priority - priority of job to be scheduled
	 * @param id - id of job to be scheduled
    *
    * @return true if add job is ok
	 */
	bool add(uint32_t priority, uint32_t id);


private:


	/**
    * class to implement RA patthern
	 */
	class Lock {
		public:

			/**
			 * @throw runtime_error if pthread_mutex_lock does not return 0
       	 */
			Lock(pthread_mutex_t& m):mMutex(m) { 
				int ret = pthread_mutex_lock(&mMutex); 
				if (0 != ret) throw new runtime_error("pthread_mutex_lock failed"); 
			};

			virtual ~Lock() { pthread_mutex_unlock(&mMutex); };

		private:
		
			pthread_mutex_t& mMutex;
	};

	
	/**
	 * a thread attr
	 */
	pthread_attr_t		mAttr;


	/**
	 * a conditional mutex to notify read thread
	 */
	pthread_cond_t		mCondRead;


	/**
    * a mutex to protect mJobQueue
	 */
	pthread_mutex_t	mMutex;


	/**
	 * true if shutdown read thread
	 */
	atomic_bool					mShutdown;
	

	/**
	 * read thread tid
	 */
	pthread_t			mTid;
	
};


