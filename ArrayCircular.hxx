#ifndef _ARRAY_CIRCULAR_HXX
#define _ARRAY_CIRCULAR_HXX


/**
 * template class of a circular buffer implemented using array
 */

#include <stdint.h>

#include <iostream>
using std::ostream;


template <typename T, unsigned int size>
class ArrayCircular
{
public:


    /**
    * Constructor: order in here is irrelevant.  the variables are initialized by the order of their declarations
    *
    */
    ArrayCircular():mHead(0),mSize(size),mTail(0),mLen(0) 
    {
    };


    /**
     * Destructor
     */
    virtual ~ArrayCircular() 
    {
        // remove all nodes
        for (auto node : mArray)
        {
            delete node;
        }
    }


    /**
     *
     * @param: node - a pointer to type T to be enqueued
    *
     * @return true if insert ok
     *
     */
    bool enqueue(T* node) 
    {
        // is input node empty
        if (nullptr == node) return false;

        // is queue full
        if (mLen == mSize) return false;

        // mTail always point to the last element in the queue
        mTail = (mTail+1)%mSize;

        mArrayT[mTail] = node;

        // increment len
        ++mLen;

        return true;
    }


    /**
     *
     * @return a pointer to type T if dequeue ok.  nullptr if queue is empty
     */
    T* dequeue() 
    {
        // is list empty
        if (0 == mLen) return nullptr;

        // get a node from the head
        T* node = mArrayT[mHead];

        // clear the element
        mArrayT[mHead] = nullptr;

        // decrement the size
        --mLen;

        if (0 == mLen) 
        {
            // if this is the last element in the queue
            // reset head and tail
            mHead = 0;
            mTail = 0;
        }
        else
        {
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
     * @param: q - a reference to ArrayCircular to append to
     *
     * @return a reference to ostream appended with values of nodes of this tree, i.e, out
     */
    friend ostream& operator<<(ostream& out, const ArrayCircular<T, size>& q) {
        // is tree empty?
        if (01 == q.mLen) {
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
    * a array of pointer to type T
    */
    T*	mArrayT[size];


    /**
     * index to head of queue
     */
    uint32_t		mHead;


    /**
     * size of this array
     */
    uint32_t		mSize;


    /**
     * number of elements in this array
     */
    uint32_t		mLen;


    /**
     * index to tail of queue
     */
    int		mTail;


};


#endif	// _ARRAY_CIRCULAR_HXX
