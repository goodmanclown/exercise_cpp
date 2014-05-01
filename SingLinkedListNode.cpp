#include "SingLinkedListNode.hxx"

void SingLinkedListNode::insert(SingLinkedListNodePtr ptr)
{
	if (NULL == ptr) return;

	if (NULL == mNextPtr) mNextPtr = ptr;
	else {
		// set the old next ptr as the new node's next ptr
		ptr->setNextPtr(mNextPtr);
		
		// set the new node as next ptr
		mNextPtr = ptr;
	}
}


SingLinkedListNode& SingLinkedListNode::operator=(const SingLinkedListNode& rhs)
{
	if (this == &rhs) return *this;

	mNextPtr = rhs.mNextPtr;
	mValue = rhs.mValue;

	return *this;
}


