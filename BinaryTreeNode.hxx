#pragma once

#include <stdint.h>

#include <iostream>
#include <memory>

using std::ostream;

template<typename T>
class BinaryTreeNode;

template<typename T>
using BinaryTreeNodePtr = std::shared_ptr<BinaryTreeNode<T>>;

/**
 * a template class representing the node of a bi-nary tree
 */ 
template<typename T>
class BinaryTreeNode {

public:

	/**
	 * Constructor
	 *
	 * @param: value - value of this node
	 *
	 */
	explicit BinaryTreeNode(T value):mValue(value) { };


	/**
	 * Constructor
	 */
	BinaryTreeNode() = delete;


	/**
	 * Destructor
	 */
	virtual ~BinaryTreeNode() = default;


	/**
	 * @return mGreaterThanEqualToPtr
     */
	BinaryTreeNodePtr<T> getGreaterThanEqualToPtr() const { return mGreaterThanEqualToPtr; };


	/**
	 * @return mLessThanPtr
     */
	BinaryTreeNodePtr<T> getLessThanPtr() const { return mLessThanPtr; };


	/**
	 * @return mGreaterThanEqualToPtr
     */
	void setGreaterThanEqualToPtr(BinaryTreeNodePtr<T> node) { mGreaterThanEqualToPtr.swap(node); };


	/**
	 * @return mLessThanPtr
     */
	void setLessThanPtr(BinaryTreeNodePtr<T> node) { mLessThanPtr.swap(node); };


	/**
	 * @param rhs - a reference to a BinaryTreeNode to determine which ptr to return
     * 				 if input has value greater than this node, return mGreaterThanEqualToPtr
     * 				 if input has value less than this node, return mLessThanPtr
	 *
	 * @return value of mGreaterThanEqualToPtr, or mLessThanPtr
     */
	BinaryTreeNodePtr<T> getPtr(const BinaryTreeNode<T>& rhs) const { 
		if (rhs < *this) return mLessThanPtr; 
        else return mGreaterThanEqualToPtr; 
	};


	/**
	 * @param rhs - a reference to a BinaryTreeNode to determine which ptr to return
    * 				 if input has value greater than this node, return mGreaterThanEqualToPtr
    * 				 if input has value less than this node, return mLessThanPtr
	 *
	 * @return value of mGreaterThanEqualToPtr, or mLessThanPtr
    */
	BinaryTreeNodePtr<T> getPtr(T rhs) const
	{ 
		if (*this > rhs) return mLessThanPtr; 
        else return mGreaterThanEqualToPtr; 
	};



	/**
	 * @param ptr - a pointer to a BinayTreeNode object to be set to mGreaterThanEqualToPtr, or mLessThanPtr
    * 				 if input has value greater than this node, set to mGreaterThanEqualToPtr
    * 				 if input has value less than this node, set to mLessThanPtr
    */
	void setPtr(BinaryTreeNodePtr<T> ptr)
	{
		// is input a null pointer
		if (nullptr == ptr) return;

		if (*ptr < *this) mLessThanPtr.swap(ptr);
        else mGreaterThanEqualToPtr.swap(ptr);
	};


	/**
	 * @param rhs - a reference to a BinaryTreeNode to determine which ptr to remove
    * 				 if input has value same as mGreaterThanEqualToPtr, set mGreaterThanEqualToPtr as NULL
    * 				 if input has value same as mLessThanPtr, set mLessThanPtr as NULL
	 *
	 * @return true if remove ok, false if input value does not match with this node, or this node has no ptr set
    */
	bool remove(const BinaryTreeNode<T>& rhs)
	{ 
		if (nullptr != mGreaterThanEqualToPtr && rhs == *mGreaterThanEqualToPtr) {
			mGreaterThanEqualToPtr.reset();
			return true;
		}
		else if (nullptr != mLessThanPtr && rhs == *mLessThanPtr) {
			mLessThanPtr.reset();
			return true;
		}

		return false;
	};


	/**
	 * less than operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if mValue is less than rhs.mValue
	 */
	bool operator<(const BinaryTreeNode<T>& rhs) const { return (mValue < rhs.mValue); };


	/**
	 * greater than operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if mValue is greater than rhs.mValue
	 */
	bool operator>(const BinaryTreeNode<T>& rhs) const { return (mValue > rhs.mValue); };


	/**
	 * comparison operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if input is same as this one
	 */
	bool operator==(const BinaryTreeNode<T>& rhs) const { return (mValue == rhs.mValue); };


	/**
	 * less than operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if mValue is less than rhs
	 */
	bool operator<(T rhs) const { return (mValue < rhs); };


	/**
	 * greater than operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if mValue is greater than rhs
	 */
	bool operator>(T rhs) const { return (mValue > rhs); };


	/**
	 * comparison operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if input is same as this one
	 */
	bool operator==(T rhs) const { return (mValue == rhs); };


	/**
	 * @return mValue
	 */
	const T getValue() const { return mValue; };


	/**
	 * append to output stream
	 *
	 * @param: out - a reference to output stream to append to
	 *
	 * @return a reference to ostream appended with value of this node, i.e, out
	 */
	friend ostream& operator<<(ostream& out, const BinaryTreeNode<T>& node) { return (out << node.mValue); };


private:

	/**
	 * Copy Constructor
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	BinaryTreeNode(const BinaryTreeNode<T>& rhs) = delete;


	/**
	 * assign operator
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>& rhs) = delete;


	/**
	 * pointer to node greater than value to this node
	 */
	BinaryTreeNodePtr<T> 	mGreaterThanEqualToPtr;


	/**
	 * pointer to node greater than value to this node
	 */
	BinaryTreeNodePtr<T> 	mLessThanPtr;


	/**
	 * value of this node
	 */
	T	mValue;

};

