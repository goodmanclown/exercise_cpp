#ifndef __BINARY_TREE_SAME_LEVEL_LINK_NODE_HXX_
#define __BINARY_TREE_SAME_LEVEL_LINK_NODE_HXX_

#include <stdint.h>

#include <iostream>
using std::ostream;


/**
 * a template class representing the node of a bi-nary tree, with an additional link to the same level node to the right
 * each node has a left and right child node
 * left child node has value less than this node
 * right child node has value greater than or equal to this node (only 1 duplicate is allowed)
 * 
 * the type T should support operator<, operator>=, and operator==, and operator<<
 */ 
template<typename T>
class BinaryTreeSameLevelLinkNode {

public:

	/**
	 * Constructor (make it explicit to prevent implicity conversion)
	 *
	 * @param: value - value of this node
	 *
	 */
	explicit BinaryTreeSameLevelLinkNode(T value):mGreaterThanEqualToPtr(NULL),mLessThanPtr(NULL),mSameLevelPtr(NULL),mValue(value) { };


	/**
	 * Destructor
	 */
	virtual ~BinaryTreeSameLevelLinkNode() {};


	/**
	 * @return mGreaterThanEqualToPtr
    */
	BinaryTreeSameLevelLinkNode<T>* getGreaterThanEqualToPtr() const { return mGreaterThanEqualToPtr; };


	/**
	 * @return mLessThanPtr
    */
	BinaryTreeSameLevelLinkNode<T>* getLessThanPtr() const { return mLessThanPtr; };


	/**
	 * @param rhs - a reference to a BinaryTreeSameLevelLinkNode to determine which ptr to return
    * 				 if input has value greater than or equal to this node, return mGreaterThanEqualToPtr
    * 				 if input has value less than this node, return mLessThanPtr
	 *
	 * @return value of mGreaterThanEqualToPtr, or mLessThanPtr
    */
	BinaryTreeSameLevelLinkNode<T>* getPtr(const BinaryTreeSameLevelLinkNode<T>& rhs) const { 
		return getPtr(rhs.mValue);
	};


	/**
	 * @param rhs - a reference to a type T to determine which ptr to return
    * 				 if input has value greater than or equal to this node, return mGreaterThanEqualToPtr
    * 				 if input has value less than this node, return mLessThanPtr
	 *
	 * @return value of mGreaterThanEqualToPtr, or mLessThanPtr
    */
	BinaryTreeSameLevelLinkNode<T>* getPtr(const T& rhs) const
	{ 
		if (rhs >= *this) return mGreaterThanEqualToPtr; 
		else if (rhs < *this) return mLessThanPtr; 

		return NULL;
	};


	/**
	 * @param ptr - a pointer to a BinayTreeSameLevelLinkNode object to be set to mGreaterThanEqualToPtr, or mLessThanPtr
    * 				 if input has value greater than or equal to this node, set to mGreaterThanEqualToPtr
    * 				 if input has value less than this node, set to mLessThanPtr
    *
    * @return true if set is ok
    */
	bool setPtr(BinaryTreeSameLevelLinkNode<T>* ptr)
	{
		// is input a null pointer
		if (NULL == ptr) return false;

		if ((*ptr >= *this) && (NULL == mGreaterThanEqualToPtr)) {
			mGreaterThanEqualToPtr = ptr;
			return true;
		}
		else if ((*ptr < *this) && (NULL == mLessThanPtr)) {
			mLessThanPtr = ptr;
			return true;
		}

		return false;
	};


	/**
	 * @param ptr - a pointer to a BinayTreeSameLevelLinkNode object to be set to mSameLevePtr
    *
    * @return true if set is ok
    */
	bool setSameLevelPtr(BinaryTreeSameLevelLinkNode<T>* ptr)
	{
		// is input a null pointer
		if (NULL == ptr) return false;

		if (NULL == mSameLevelPtr) {
			mSameLevelPtr = ptr;
			return true;
		}

		return false;
	};


	/**
	 * @param rhs - a reference to a BinaryTreeSameLevelLinkNode to determine which ptr to remove
    * 				 if input has value same as mGreaterThanEqualToPtr, set mGreaterThanEqualToPtr as NULL
    * 				 if input has value same as mLessThanPtr, set mLessThanPtr as NULL
	 *
	 * @return true if remove ok, false if input value does not match with this node, or this node has no ptr set
    */
	bool remove(const BinaryTreeSameLevelLinkNode<T>& rhs)
	{ 
		if (NULL != mGreaterThanEqualToPtr && rhs == *mGreaterThanEqualToPtr) {
			mGreaterThanEqualToPtr = NULL;
			return true;
		}
		else if (NULL != mLessThanPtr && rhs == *mLessThanPtr) {
			mLessThanPtr = NULL;
			return true;
		}

		return false;
	};


	/**
	 * less than operator
	 *
	 * @param: rhs - a reference to a BinaryTreeSameLevelLinkNode to compare with
	 *
	 * @return true if mValue is less than rhs.mValue
	 */
	bool operator<(const BinaryTreeSameLevelLinkNode<T>& rhs) const { return (mValue < rhs.mValue); };


	/**
	 * greater than or equal to operator
	 *
	 * @param: rhs - a reference to a BinaryTreeSameLevelLinkNode to compare with
	 *
	 * @return true if mValue is greater than or equal to rhs.mValue
	 */
	bool operator>=(const BinaryTreeSameLevelLinkNode<T>& rhs) const { return (mValue >= rhs.mValue); };


	/**
	 * comparison operator
	 *
	 * @param: rhs - a reference to a BinaryTreeSameLevelLinkNode to compare with
	 *
	 * @return true if input is same as this one
	 */
	bool operator==(const BinaryTreeSameLevelLinkNode<T>& rhs) const { return (mValue == rhs.mValue); };


	/**
	 * less than operator
	 *
	 * @param: rhs - a reference to a type T to compare with
	 *
	 * @return true if mValue is less than rhs
	 */
	bool operator<(const T& rhs) const { return (mValue < rhs); };


	/**
	 * greater than or equal to operator
	 *
	 * @param: rhs - a reference to a type T to compare with
	 *
	 * @return true if mValue is greater than or equal to rhs
	 */
	bool operator>=(const T& rhs) const { return (mValue >= rhs); };


	/**
	 * comparison operator
	 *
	 * @param: rhs - a reference to a type T to compare with
	 *
	 * @return true if input is same as this one
	 */
	bool operator==(const T& rhs) const { return (mValue == rhs); };


	/**
	 * @return mValue
	 */
	const T& getValue() const { return mValue; };


	/**
	 * append to output stream
	 *
	 * @param: out - a reference to output stream to append to
	 * @param: node - a reference to BinaryTreeSameLevelLinkNode to be appended to the output stream
	 *
	 * @return a reference to ostream appended with value of this node, i.e, out
	 */
	friend ostream& operator<<(ostream& out, const BinaryTreeSameLevelLinkNode<T>& node) { return (out << node.mValue); };


private:

	/**
	 * Copy Constructor (disabled)
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	BinaryTreeSameLevelLinkNode(const BinaryTreeSameLevelLinkNode<T>& rhs) {};


	/**
	 * assign operator (disabled)
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	BinaryTreeSameLevelLinkNode<T>& operator=(const BinaryTreeSameLevelLinkNode<T>& rhs) { };


	/**
	 * pointer to node greater than or equal to value to this node
	 */
	BinaryTreeSameLevelLinkNode<T>* 	mGreaterThanEqualToPtr;


	/**
	 * pointer to node greater than value to this node
	 */
	BinaryTreeSameLevelLinkNode<T>* 	mLessThanPtr;


	/**
	 * pointer to node at the same level to the right
	 */
	BinaryTreeSameLevelLinkNode<T>* 	mSameLevelPtr;


	/**
	 * value of this node
	 */
	T	mValue;

};


#endif // __BINARY_TREE_SAME_LEVEL_LINK_NODE_HXX_
