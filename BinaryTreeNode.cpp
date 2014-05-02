#include "BinaryTreeNode.hxx"

template<typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getPtr(const BinaryTreeNode<T>& rhs) const 
{ 
	if (rhs > *this) return mGreaterThanPtr; 
	else if (rhs < *this) return mLessThanPtr; 

	return NULL;
}


template<typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getPtr(T rhs) const 
{ 
	if (*this < rhs) return mGreaterThanPtr; 
	else if (*this > rhs) return mLessThanPtr; 

	return NULL;
}


template<typename T>
void BinaryTreeNode<T>::setPtr(BinaryTreeNode<T>* ptr)
{
	// is input a null pointer
	if (NULL == ptr) return;

	if (*ptr > *this) mGreaterThanPtr = ptr;
	else if (*ptr < *this) mLessThanPtr = ptr;
}


template<typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(const BinaryTreeNode<T>& rhs)
{
	if (this == &rhs) return *this;

	mGreaterThanPtr = rhs.mGreaterThanPtr;
	mLessThanPtr = rhs.mLessThanPtr;
	mValue = rhs.mValue;

	return *this;
}


template<typename T>
bool BinaryTreeNode<T>::remove(const BinaryTreeNode<T>& rhs) 
{ 
	if (NULL != mGreaterThanPtr && rhs == *mGreaterThanPtr) {
		mGreaterThanPtr = NULL;
		return true;
	}
	else if (NULL != mLessThanPtr && rhs == *mLessThanPtr) {
		mLessThanPtr = NULL;
		return true;
	}

	return false;
}

