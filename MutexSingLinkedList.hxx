#include "SingLinkedList.hxx"

#include <stdint.h>
#include <pthread.h>


/**
 * class to protect a SingLinkedList with mutex
 *
 * inherited as private so that caller cannot call unprotected methods of SingLinkedList
 */ 
class MutexSingLinkedList : private SingLinkedList {

public:


	/** 
    * Constructor
	 */
	MutexSingLinkedList():SingLinkedList() { pthread_mutex_init(&mMutex, NULL); };


	/** 
    * Destructor
	 */
	virtual ~MutexSingLinkedList() { pthread_mutex_destroy(&mMutex); };

	
	/**
    * @return length of list
    */
	uint32_t getLength() const { Lock l(mMutex); return SingLinkedList::getLength(); };


	/**
    * @return a pointer to a SingLinkedListNodePtr removed from the front of the list
    */
	SingLinkedListNodePtr pop_front() { Lock l(mMutex); return SingLinkedList::pop_front(); };


	/**
	 * @param node - a pointer to SingLinkedListNode object to be added to the list
    *
    * @return true if add is ok
    */
	bool insert(SingLinkedListNodePtr node) { Lock l(mMutex); return SingLinkedList::insert(node); };


   /** 
    * append to output stream
    *   
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to MutexSingLinkedListNodePtr to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */  
	friend ostream& operator<<(ostream& out, const MutexSingLinkedList& tree) {
		Lock l(tree.mMutex);

		// is tree empty?
		if (NULL == tree.mHead) {
			return (out << "empty");
		}
		else {
			// traverse down the root to print out values of nodes
			return tree.traverse(out, *(tree.mHead));
		}
	};


private:


	/**
	 * a class to implement the RA pattern
	 */
	class Lock {

		public:
	
		   /** 
          * Constructor
          */
			Lock(pthread_mutex_t& m):mMutex(m) { pthread_mutex_lock(&mMutex); };

		   /** 
          * Destructor
          */
			virtual ~Lock() { pthread_mutex_unlock(&mMutex); };

		private:
		
		   /** 
          * a reference to a mutex to lock or unlock
          */
			pthread_mutex_t&	mMutex;

	};


	/**
    * a mutex to protect the member of SingLinkedList
	 */
	mutable pthread_mutex_t	mMutex;


};


