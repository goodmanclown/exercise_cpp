#ifndef __BINARY_TREE_NODE_HXX_
#define __BINARY_TREE_NODE_HXX_

#include <stdint.h>

#include <iostream>
using std::ostream;


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
	explicit BinaryTreeNode(T value):mGreaterThanPtr(NULL),mLessThanPtr(NULL),mValue(value) { };


	/**
	 * Destructor
	 */
	virtual ~BinaryTreeNode() {};


	/**
	 * @return mGreaterThanPtr
    */
	BinaryTreeNode<T>* getGreaterThanPtr() const { return mGreaterThanPtr; };


	/**
	 * @return mLessThanPtr
    */
	BinaryTreeNode<T>* getLessThanPtr() const { return mLessThanPtr; };


	/**
	 * @param rhs - a reference to a BinaryTreeNode to determine which ptr to return
    * 				 if input has value greater than this node, return mGreaterThanPtr
    * 				 if input has value less than this node, return mLessThanPtr
	 *
	 * @return value of mGreaterThanPtr, or mLessThanPtr
    */
	BinaryTreeNode<T>* getPtr(const BinaryTreeNode<T>& rhs) const;


	/**
	 * @param rhs - a reference to a BinaryTreeNode to determine which ptr to return
    * 				 if input has value greater than this node, return mGreaterThanPtr
    * 				 if input has value less than this node, return mLessThanPtr
	 *
	 * @return value of mGreaterThanPtr, or mLessThanPtr
    */
	BinaryTreeNode<T>* getPtr(uint32_t rhs) const;


	/**
	 * @param ptr - a pointer to a BinayTreeNode object to be set to mGreaterThanPtr, or mLessThanPtr
    * 				 if input has value greater than this node, set to mGreaterThanPtr
    * 				 if input has value less than this node, set to mLessThanPtr
    */
	void setPtr(BinaryTreeNode<T>* ptr);


	/**
	 * @param rhs - a reference to a BinaryTreeNode to determine which ptr to remove
    * 				 if input has value same as mGreaterThanPtr, set mGreaterThanPtr as NULL
    * 				 if input has value same as mLessThanPtr, set mLessThanPtr as NULL
	 *
	 * @return true if remove ok, false if input value does not match with this node, or this node has no ptr set
    */
	bool remove(const BinaryTreeNode<T>& rhs);


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
	T getValue() const { return mValue; };


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
	BinaryTreeNode(const BinaryTreeNode<T>& rhs):mGreaterThanPtr(rhs.mGreaterThanPtr),mLessThanPtr(rhs.mLessThanPtr),mValue(rhs.mValue) { };


	/**
	 * assign operator
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>& rhs);


	/**
	 * pointer to node greater than value to this node
	 */
	BinaryTreeNode<T>* 	mGreaterThanPtr;


	/**
	 * pointer to node greater than value to this node
	 */
	BinaryTreeNode<T>* 	mLessThanPtr;


	/**
	 * value of this node
	 */
	T	mValue;

};


#endif // __BINARY_TREE_NODE_HXX_
