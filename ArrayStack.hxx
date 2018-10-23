/**
 * template class of a stack implemented using array
 * the type of array must implement copy constructor and operator=
 */ 

#include <stdint.h>
#include <algorithm>

using std::copy;
using std::for_each;
using std::nothrow;

template <typename T>
class ArrayStack {

public:

	/**
	 * Constructor
    *
	 * @param size - size of array of <T> initialized, default 100
	 */
	ArrayStack(uint32_t size=100):mArrayT(0),mHead(-1),mLength(0),mSize(size) {
		// initialized an array of T of size 
		mArrayT = new T*[size];
	};


	/**
	 * Destructor
    *
	 */
	virtual ~ArrayStack() 
	{
		for_each(mArrayT, mArrayT + mLength, 
		    [] (T* node) {
			    delete node;
		    }
		);

		delete [] mArrayT;
	};


	/**
	 *
	 * @return number of elements in the array
    */
	uint32_t	length() const { return mLength; };


	/**
    * push an element T to the stack
    *
    * @param elem - a pointer to object of type T
	 *
    * @return >= 0, position of the element in the stack. -1 if stack full
    */
	int push(T* elem) {
		if (mLength >= mSize) {
			// if we are at the limit, double the size
			mSize += mSize;
			T** tempArrayT = new (nothrow) T*[mSize]; 

			// return error if can't get more memory
			if (0 == tempArrayT) return -1;

			// copy the elements over
			copy(mArrayT, mArrayT+mLength, tempArrayT);

			delete [] mArrayT;

			mArrayT = tempArrayT;
		}

		mArrayT[++mHead] = elem;

		mLength++;

		return mHead;
	};	


	/**
    * pop an element T from the stack
	 *
	 * @return an element T 
    */
	T*	pop() {

		// mLength == 0, nothing in the stack
		if (mLength == 0) return 0;
		
		mLength--;

		return mArrayT[mHead--];
	};


	/**
	 *
	 * @return size of array
    */
	uint32_t	size() const { return mSize; };

private:

	/**
	 * an array of T*
	 */
	T**		mArrayT;


	/**
	 * index to the top of the stack
    */
   int	mHead;


	/**
    * number of elements in the array
    */
   uint32_t	mLength;


	/**
    * initial size of array
    */
   uint32_t	mSize;


};


