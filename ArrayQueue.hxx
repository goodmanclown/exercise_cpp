#ifndef _ARRAY_QUEUE_HXX
#define _ARRAY_QUEUE_HXX


/**
 * template class of a queue implemented using array
 */

#include <stdint.h>

#include <iostream>
using std::ostream;


template <typename T, unsigned int size>
class ArrayQueue
{
public:


    /**
    * Constructor
    *
    */
    ArrayQueue():mHead(0),mSize(size),mTail(-1) { };


    /**
     * Destructor
     */
    virtual ~ArrayQueue() {
        // remove all nodes
        T* node = nullptr;

        while ((node = dequeue()) != nullptr) delete node;
    }


    /**
     *
     * @param: node - a pointer to type T to be enqueued
    *
     * @return true if insert ok
     *
     */
    bool enqueue(T* node) {
        // is input node empty
        if (nullptr == node) return false;

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
     * @return a pointer to type T if dequeue ok.  nullptr if queue is empty
     */
    T* dequeue() {
        // is list empty
        if (-1 == mTail) return nullptr;

        T* node = mArrayT[mHead];

        // clear the element
        mArrayT[mHead] = nullptr;

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
    friend ostream& operator<<(ostream& out, const ArrayQueue<T, size>& q) {
        // is tree empty?
        if (-1 == q.mTail) {
            return (out << "empty");
        }
        else {
            int index = q.mHead;
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
    * a array of pointer to type T
    */
    T*	mArrayT[size];


    /**
     * index to head of queue
     */
    int		        mHead;


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
