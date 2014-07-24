#ifndef _ARRAY_QUEUE_HXX
#define _ARRAY_QUEUE_HXX


/**
 * template class of a queue implemented using array
 * the type T must implement copy constructor and operator=
 */

#include <stdint.h>

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

template <typename T>
class ArrayQueue
{
public:


	/**
    * Constructor
    * @param size - size of array of <T> initialized, default 100
	 */
	ArrayQueue(uint32_t size=100):mHead(0),mLength(0),mSize(size),mTail(-1) { mArrayT = new T*[size]; };

	
	/**
	 * Destructor
	 */
	virtual ~ArrayQueue() {
   	// remove all nodes 
   	uint32_t index = mHead;

   	for (uint32_t count = 0; count < mLength; count++) {
      	T* node = mArrayT[index];

      	delete node;

      	// if reach the end of the array, wrap around
      	index = (index+1)%mSize;
   	}  
      delete [] mArrayT;
	}

	
	/**
	 *
	 * @param: node - a pointer to type T to be enqueued to the queue
    *
	 * @return true if insert ok
	 *
	 */
	bool enqueue(T* node) {
		// is input node empty
   	if (NULL == node) return false;

   	// queue is full 
   	if (mLength == mSize) return false;

   	// mTail always point to the last element in the queue
   	mTail = (mTail+1)%mSize;

   	cout << "mTail " << mTail << endl;

   	mArrayT[mTail] = node; 

   	mLength++;

   	return true;
	}


	/**
	 *
	 * @return a pointer to type T if dequeue ok
	 */
	T* dequeue() {
   	// list is empty
   	if (0 == mLength) return NULL;

   	T* node = mArrayT[mHead];

   	// clear the element
   	mArrayT[mHead] = NULL;

   	mLength--;

   	if (mLength > 0) {
      	// mHead always point to the 1st element in the queue
      	// move head to the next element, wrap around if needed
      	mHead = (mHead + 1) % mSize;

      	cout << "mHead " << mHead << endl;
   	}
   	else {
      	// if there's no more element in the queue
      	// reset head and tail
      	mHead = 0;
      	mTail = -1;
   	}

   	return node;
	}


	/**
    * @return length of this queue
    */
	uint32_t	length() const { return mLength; };


   /** 
    * append to output stream
    *   
    * @param: out - a reference to output stream to append to
    * @param: q - a reference to ArrayQueue to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */  
	friend ostream& operator<<(ostream& out, const ArrayQueue& q) {
   	// is tree empty?
   	if (0 == q.length()) {
      	return (out << "empty");
   	}
   	else {
      	uint32_t index = q.mHead;
      	for (uint32_t count = 0; count < q.length(); count++) {

         	T* node = q.mArrayT[index];

         	// append value of the input node to the output stream
         	out << *node << " ";

         	index = (index + 1) % q.mSize;
      	}
      	return out;
   	}
	}


private:


	/**
	 * index to head of queue
	 */
	uint32_t		mHead;

	
	/**
	 * length of this list
	 */
	uint32_t		mLength;


	/**
    * a array of pointer to type T
    */
	T**	mArrayT;
	

	/**
	 * size of this array
	 */
	uint32_t		mSize;


	/**
	 * index to tail of queue
	 */
	int		mTail;


};


#endif	// _ARRAY_QUEUE_HXX
