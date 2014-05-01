#include "SingLinkedListNode.hxx"

#include <iostream>

using std::ostream;

/**
 * class representing an array queue
 */ 
class ArrayQueue
{
public:


	/**
    * Constructor
	 */
	ArrayQueue(uint32_t size):mHead(0),mLength(0),mSize(size),mTail(-1) { mSingLinkedListNodePtrArray = new SingLinkedListNodePtr[size]; };

	
	/**
	 * Destructor
	 */
	virtual ~ArrayQueue();


	/**
	 *
	 * @param: value - to be enqueued to the queue
    *
	 * @return true if insert ok
	 *
	 */
	bool enqueue(uint32_t value);


	/**
	 *
	 * @return true if dequeue ok
	 */
	SingLinkedListNodePtr dequeue();


	/**
    * @return length of this queue
    */
	uint32_t	length() { return mLength; };


   /** 
    * append to output stream
    *   
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to ArrayQueue to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */  
	friend ostream& operator<<(ostream& out, const ArrayQueue& tree);


private:


	/**
	 * ptr to head of queue
	 */
	uint32_t		mHead;

	
	/**
	 * length of this list
	 */
	uint32_t		mLength;


	/**
    * a list of node
    */
	SingLinkedListNodePtr*	mSingLinkedListNodePtrArray;
	

	/**
	 * size of this array
	 */
	uint32_t		mSize;


	/**
	 * ptr to tail of queue
	 */
	int		mTail;


};


