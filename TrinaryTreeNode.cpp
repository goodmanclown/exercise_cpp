#include "TrinaryTreeNode.hxx"

TrinaryTreeNodePtr TrinaryTreeNode::getPtr(const TrinaryTreeNode& rhs) const 
{ 
	if (rhs == *this) return mEqualToPtr; 
	else if (rhs > *this) return mGreaterThanPtr; 
	else if (rhs < *this) return mLessThanPtr; 

	return NULL;
}


TrinaryTreeNodePtr TrinaryTreeNode::getPtr(uint32_t rhs) const 
{ 
	if (*this == rhs) return mEqualToPtr; 
	else if (*this < rhs) return mGreaterThanPtr; 
	else if (*this > rhs) return mLessThanPtr; 

	return NULL;
}


void TrinaryTreeNode::setPtr(TrinaryTreeNodePtr ptr)
{
	// is input a null pointer
	if (NULL == ptr) return;

	if (*ptr == *this) mEqualToPtr = ptr;
	else if (*ptr > *this) mGreaterThanPtr = ptr;
	else if (*ptr < *this) mLessThanPtr = ptr;
}


TrinaryTreeNode& TrinaryTreeNode::operator=(const TrinaryTreeNode& rhs)
{
	if (this == &rhs) return *this;

	mEqualToPtr = rhs.mEqualToPtr;
	mGreaterThanPtr = rhs.mGreaterThanPtr;
	mLessThanPtr = rhs.mLessThanPtr;
	mValue = rhs.mValue;

	return *this;
}


bool TrinaryTreeNode::remove(const TrinaryTreeNode& rhs) 
{ 
	if (NULL != mEqualToPtr && rhs == *mEqualToPtr) {
		mEqualToPtr = NULL;
		return true;
	}
	else if (NULL != mGreaterThanPtr && rhs == *mGreaterThanPtr) {
		mGreaterThanPtr = NULL;
		return true;
	}
	else if (NULL != mLessThanPtr && rhs == *mLessThanPtr) {
		mLessThanPtr = NULL;
		return true;
	}

	return false;
}

