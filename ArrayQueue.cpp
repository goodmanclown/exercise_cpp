#include "ArrayQueue.hxx"

using namespace std;

ArrayQueue::~ArrayQueue()
{
	// remove all nodes 
	uint32_t index = mHead;
	for (uint32_t count = 0; count < mLength; count++) {
		SingLinkedListNodePtr node = mSingLinkedListNodePtrArray[index];

		delete node;

		// if reach the end of the array, wrap around
		index = (index+1)%mSize;
	}	

	delete mSingLinkedListNodePtrArray;
}


bool ArrayQueue::enqueue(uint32_t value)
{
	SingLinkedListNodePtr node = new (nothrow) SingLinkedListNode(value);

	// is new ok? 
	if (NULL == node) return false;

	// queue is full
	if (mLength == mSize) return false;

	// mTail always point to the last element in the queue
	mTail = (mTail+1)%mSize;

	cout << "mTail " << mTail << endl;

	mSingLinkedListNodePtrArray[mTail] = node;

	mLength++;

	return true;
}

		
SingLinkedListNodePtr ArrayQueue::dequeue()
{
	// list is empty
	if (0 == mLength) return NULL;

	SingLinkedListNodePtr node = mSingLinkedListNodePtrArray[mHead];

	// clear the element
	mSingLinkedListNodePtrArray[mHead] = NULL;

	mLength--;

	if (mLength > 0) {
		// mHead alwasy point to the 1st element in the queue
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

		
ostream& operator<<(ostream& out, const ArrayQueue& tree)
{
	// is tree empty?
	if (0 == tree.mLength) {
		return (out << "empty");
	}
	else {
		uint32_t index = tree.mHead;
		for (uint32_t count = 0; count < tree.mLength; count++) {

			SingLinkedListNodePtr node = tree.mSingLinkedListNodePtrArray[index];

			// append value of the input node to the output stream
			out << *node << " ";

			index = (index + 1) % tree.mSize;
		}	
		return out;
	}
}


