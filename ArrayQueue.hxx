#ifndef _ARRAY_QUEUE_HXX
#define _ARRAY_QUEUE_HXX


/**
 * template class of a queue implemented using array
 * the type T must implement copy constructor and operator=
 */

#include <stdint.h>

#include <iostream>
using std::ostream;


template <typename T>
class ArrayQueue
{
public:


	/**
    * Constructor
    * @param size - size of array of <T> initialized, default 100
	 */
	ArrayQueue(uint32_t size=100):mHead(0),mSize(size),mTail(-1) { mArrayT = new T*[size]; };

	
	/**
	 * Destructor
	 */
	virtual ~ArrayQueue() {
   	// remove all nodes 
      T* node = NULL;
   	while ((node = dequeue()) != NULL)
      	delete node;

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

		// std::cout << "mHead " << mHead << " mTail " << mTail << std::endl;

   	// is queue full 
		if (-1 != mTail) {
   		if (mHead < mTail) {
				if ((mTail - mHead + 1) == mSize) return false;
			}
			else {
				if ((mHead - mTail) == 1) return false;
			}
		}

   	// mTail always point to the last element in the queue
   	mTail = (mTail+1)%mSize;

   	mArrayT[mTail] = node; 

   	return true;
	}


	/**
	 *
	 * @return a pointer to type T if dequeue ok
	 */
	T* dequeue() {
   	// is list empty
   	if (-1 == mTail) return NULL;

   	T* node = mArrayT[mHead];

   	// clear the element
   	mArrayT[mHead] = NULL;

   	if (mHead == mTail) {
      	// if this is the last element in the queue
      	// reset head and tail
      	mHead = 0;
      	mTail = -1;
   	}
		else {
  	   	// mHead always point to the 1st element in the queue
  	    	// move head to the next element, wrap around if needed
  	    	mHead = (mHead + 1) % mSize;
		}

   	return node;
	}


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
   	if (-1 == q.mTail) {
      	return (out << "empty");
   	}
   	else {
      	uint32_t index = q.mHead;
      	while (index != q.mTail) {

         	T* node = q.mArrayT[index];

         	// append value of the input node to the output stream
         	out << *node << " ";

         	index = (index + 1) % q.mSize;
      	}
		
			// append the last node as well
         T* node = q.mArrayT[q.mTail];
         out << *node << " ";

      	return out;
   	}
	}


private:


	/**
	 * index to head of queue
	 */
	uint32_t		mHead;

	
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
