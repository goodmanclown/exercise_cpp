#ifndef __TRINARY_TREE_NODE_HXX_
#define __TRINARY_TREE_NODE_HXX_

#include <stdint.h>

#include <iostream>
using std::ostream;

class TrinaryTreeNode;

typedef TrinaryTreeNode* const TrinaryTreeNodePtr;


/**
 * class representing the node of a tri-nary tree
 */ 
class TrinaryTreeNode {

public:

	/**
	 * Constructor
	 *
	 * @param: value - value of this node
	 *
	 */
	explicit TrinaryTreeNode(uint32_t value):mEqualToPtr(NULL),mGreaterThanPtr(NULL),mLessThanPtr(NULL),mValue(value) { };


	/**
	 * Destructor
	 */
	virtual ~TrinaryTreeNode() {};


	/**
	 * @return mEqualToPtr
    */
	TrinaryTreeNodePtr getEqualToPtr() const { return mEqualToPtr; };


	/**
	 * @return mGreaterThanPtr
    */
	TrinaryTreeNodePtr getGreaterThanPtr() const { return mGreaterThanPtr; };


	/**
	 * @return mLessThanPtr
    */
	TrinaryTreeNodePtr getLessThanPtr() const { return mLessThanPtr; };


	/**
	 * @param rhs - a reference to a TrinaryTreeNode to determine which ptr to return
    * 				 if input has value same as this node, return mEqualToPtr
    * 				 if input has value greater than this node, return mGreaterThanPtr
    * 				 if input has value less than this node, return mLessThanPtr
	 *
	 * @return value of mEqualToPtr or mGreaterThanPtr, or mLessThanPtr
    */
	TrinaryTreeNodePtr getPtr(const TrinaryTreeNode& rhs) const;


	/**
	 * @param rhs - a reference to a TrinaryTreeNode to determine which ptr to return
    * 				 if input has value same as this node, return mEqualToPtr
    * 				 if input has value greater than this node, return mGreaterThanPtr
    * 				 if input has value less than this node, return mLessThanPtr
	 *
	 * @return value of mEqualToPtr or mGreaterThanPtr, or mLessThanPtr
    */
	TrinaryTreeNodePtr getPtr(uint32_t rhs) const;


	/**
	 * @param ptr - a pointer to a TrinayTreeNode object to be set to mEqualToPtr or mGreaterThanPtr, or mLessThanPtr
    * 				 if input has value same as this node, set to mEqualToPtr
    * 				 if input has value greater than this node, set to mGreaterThanPtr
    * 				 if input has value less than this node, set to mLessThanPtr
    */
	void setPtr(TrinaryTreeNodePtr ptr);


	/**
	 * @param rhs - a reference to a TrinaryTreeNode to determine which ptr to remove
    * 				 if input has value same as mEqualToPtr, set mEqualToPtr as NULL
    * 				 if input has value same as mGreaterThanPtr, set mGreaterThanPtr as NULL
    * 				 if input has value same as mLessThanPtr, set mLessThanPtr as NULL
	 *
	 * @return true if remove ok, false if input value does not match with this node, or this node has no ptr set
    */
	bool remove(const TrinaryTreeNode& rhs);


	/**
	 * less than operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if mValue is less than rhs.mValue
	 */
	bool operator<(const TrinaryTreeNode& rhs) const { return (mValue < rhs.mValue); };


	/**
	 * greater than operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if mValue is greater than rhs.mValue
	 */
	bool operator>(const TrinaryTreeNode& rhs) const { return (mValue > rhs.mValue); };


	/**
	 * comparison operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if input is same as this one
	 */
	bool operator==(const TrinaryTreeNode& rhs) const { return (mValue == rhs.mValue); };


	/**
	 * less than operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if mValue is less than rhs
	 */
	bool operator<(uint32_t rhs) const { return (mValue < rhs); };


	/**
	 * greater than operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if mValue is greater than rhs
	 */
	bool operator>(uint32_t rhs) const { return (mValue > rhs); };


	/**
	 * comparison operator
	 *
	 * @param: rhs - value to compared with
	 *
	 * @return true if input is same as this one
	 */
	bool operator==(uint32_t rhs) const { return (mValue == rhs); };


	/**
	 * @return mValue
	 */
	uint32_t getValue() const { return mValue; };


	/**
	 * append to output stream
	 *
	 * @param: out - a reference to output stream to append to
	 *
	 * @return a reference to ostream appended with value of this node, i.e, out
	 */
	friend ostream& operator<<(ostream& out, const TrinaryTreeNode& node) { return (out << node.mValue); };


private:

	/**
	 * Copy Constructor
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	TrinaryTreeNode(const TrinaryTreeNode& rhs):mEqualToPtr(rhs.mEqualToPtr),mGreaterThanPtr(rhs.mGreaterThanPtr),mLessThanPtr(rhs.mLessThanPtr),mValue(rhs.mValue) { };


	/**
	 * assign operator
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	TrinaryTreeNode& operator=(const TrinaryTreeNode& rhs);


	/**
	 * pointer to node equal in value to this node
	 */
	TrinaryTreeNode* 	mEqualToPtr;


	/**
	 * pointer to node greater than value to this node
	 */
	TrinaryTreeNode* 	mGreaterThanPtr;


	/**
	 * pointer to node greater than value to this node
	 */
	TrinaryTreeNode* 	mLessThanPtr;


	/**
	 * value of this node
	 */
	uint32_t	mValue;

};


#endif // __TRINARY_TREE_NODE_HXX_
