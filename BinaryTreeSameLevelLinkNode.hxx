#ifndef __BINARY_TREE_SAME_LEVEL_LINK_NODE_HXX_
#define __BINARY_TREE_SAME_LEVEL_LINK_NODE_HXX_

#include <stdint.h>

#include <iostream>
using std::ostream;


/**
 * a class representing the node of a bi-nary tree
 * each node has a left and right child node, with an additional link to the same level node to the right
 */
class BinaryTreeSameLevelLinkNode {

public:

    /**
     * Constructor
     *
     * @param: value - value of this node
     *
     */
    BinaryTreeSameLevelLinkNode(uint32_t value):mLeftPtr(NULL),mRightPtr(NULL),mSameLevelPtr(NULL),mValue(value) { };


    /**
     * Destructor
     */
    virtual ~BinaryTreeSameLevelLinkNode() {};


    /**
     * @return mLeftPtr
    */
    BinaryTreeSameLevelLinkNode* getLeftPtr() const {
        return mLeftPtr;
    };


    /**
     * @return mRightPtr
    */
    BinaryTreeSameLevelLinkNode* getRightPtr() const {
        return mRightPtr;
    };


    /**
     * @return mSameLevelPtr
    *
    */
    BinaryTreeSameLevelLinkNode* getSameLevelPtr() const {
        return mSameLevelPtr;
    };


    /**
     * @param ptr - a pointer to a BinayTreeSameLevelLinkNode object to be set to mLeftPtr
    *
    */
    void setLeftPtr(BinaryTreeSameLevelLinkNode* ptr)
    {
        // is input a null pointer
        if (NULL == ptr) return;

        mLeftPtr = ptr;
    };


    /**
     * @param ptr - a pointer to a BinayTreeSameLevelLinkNode object to be set to mRightPtr
    *
    */
    void setRightPtr(BinaryTreeSameLevelLinkNode* ptr)
    {
        // is input a null pointer
        if (NULL == ptr) return;

        mRightPtr = ptr;
    };


    /**
     * @param ptr - a pointer to a BinayTreeSameLevelLinkNode object to be set to mSameLevePtr
    *
    */
    void setSameLevelPtr(BinaryTreeSameLevelLinkNode* ptr)
    {
        // is input a null pointer
        if (NULL == ptr) return;

        mSameLevelPtr = ptr;
    };


    /**
     * less than operator
     *
     * @param: rhs - a reference to a BinaryTreeSameLevelLinkNode to compare with
     *
     * @return true if mValue is less than rhs.mValue
     */
    bool operator<(const BinaryTreeSameLevelLinkNode& rhs) const {
        return (mValue < rhs.mValue);
    };


    /**
     * greater than operator
     *
     * @param: rhs - a reference to a BinaryTreeSameLevelLinkNode to compare with
     *
     * @return true if mValue is greater than or equal to rhs.mValue
     */
    bool operator>=(const BinaryTreeSameLevelLinkNode& rhs) const {
        return (mValue >= rhs.mValue);
    };


    /**
     * append to output stream
     *
     * @param: out - a reference to output stream to append to
     * @param: node - a reference to BinaryTreeSameLevelLinkNode to be appended to the output stream
     *
     * @return a reference to ostream appended with value of this node, i.e, out
     */
    friend ostream& operator<<(ostream& out, const BinaryTreeSameLevelLinkNode& node) {
        return (out << node.mValue);
    };


private:

    /**
     * Copy Constructor (disabled)
     *
     * @param: rhs - value to be copied from
     *
     */
    BinaryTreeSameLevelLinkNode(const BinaryTreeSameLevelLinkNode& rhs) {};


    /**
     * assign operator (disabled)
     *
     * @param: rhs - value to be copied from
     *
     */
    BinaryTreeSameLevelLinkNode& operator=(const BinaryTreeSameLevelLinkNode& rhs) {
        return *this;
    };


    /**
     * pointer to left child node
     */
    BinaryTreeSameLevelLinkNode* 	mLeftPtr;


    /**
     * pointer to right child node
     */
    BinaryTreeSameLevelLinkNode* 	mRightPtr;


    /**
     * pointer to node at the same level to the right
     */
    BinaryTreeSameLevelLinkNode* 	mSameLevelPtr;


    /**
     * value of this node
     */
    uint32_t	mValue;

};


#endif // __BINARY_TREE_SAME_LEVEL_LINK_NODE_HXX_
