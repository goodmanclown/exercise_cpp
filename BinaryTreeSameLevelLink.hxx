#ifndef __BINARY_TREE_SAME_LEVEL_LINK_HXX_
#define __BINARY_TREE_SAME_LEVEL_LINK_HXX_

#include "BinaryTreeSameLevelLinkNode.hxx"
#include "ArrayQueue.hxx"

#include <stdint.h>
#include <iostream>

using std::ostream;


/**
 * class representing a binary tree
 *
 * left node has value less than parent
 * right node has value greater than or equal to parent
 *
 * each node has a link to the same level node on its right
 */
class BinaryTreeSameLevelLink
{
public:


    /**
     * Constructor
     */
    BinaryTreeSameLevelLink():mRoot(NULL) { };


    /**
     * Destructor
     */
    virtual ~BinaryTreeSameLevelLink()
    {
        // remove all nodes
        remove(mRoot);

        mRoot = NULL;
    };



    /**
     *
     * traverse the tree breath first and link nodes at the same level
     */
    void linkSameLevelNode()
    {
        // is the tree empty
        if (NULL == mRoot) return;

        // initialize queue to help with the traversal
        ArrayQueue<BinaryTreeSameLevelLinkNode> q(8);

        // insert the root to the queue to kick off the traversal
        q.enqueue(mRoot);

        uint32_t numberOfCurrentLevelNode = 1;
        uint32_t numberOfNextLevelNode = 0;
        uint32_t numberOfNodeLinked = 0;
        BinaryTreeSameLevelLinkNode* lastNodeFromQueue = NULL;

        BinaryTreeSameLevelLinkNode* outNode = NULL;

        // dequeue nodes from the queue until the queue is empty
        while ((outNode = q.dequeue()) != NULL) {

            // qeue left node, if any
            if (NULL != outNode->getLeftPtr()) {
                q.enqueue(outNode->getLeftPtr());

                // inc number of nodes at the next level
                numberOfNextLevelNode++;
            }

            // queue right node, if any
            if (NULL != outNode->getRightPtr()) {
                q.enqueue(outNode->getRightPtr());

                // inc number of nodes at the next level
                numberOfNextLevelNode++;
            }

            // check if there's already a node taken from the queue
            if (lastNodeFromQueue != NULL) {
                // link them together
                lastNodeFromQueue->setSameLevelPtr(outNode);
            }

            // set this node as last node taken from the queue
            lastNodeFromQueue = outNode;

            // increment the number of nodes linked
            numberOfNodeLinked++;
            if (numberOfNodeLinked == numberOfCurrentLevelNode) {
                // done with all the nodes at the current level
                numberOfCurrentLevelNode = numberOfNextLevelNode;

                numberOfNextLevelNode = 0;
                numberOfNodeLinked = 0;
                lastNodeFromQueue = NULL;
            }
        } 	// while ((outNode = q.dequeue()) != NULL) {
    };


    /**
     *
     * @param: node - to be inserted to the tree
     *
     * @return true if insert is ok.  if false, caller should release the memory of the input node
     *
     */
    bool insert(BinaryTreeSameLevelLinkNode* node)
    {
        // if the input is NULL, just return
        if (NULL == node) return false;

        if (NULL == mRoot) {
            // no node yet
            // just add it to the root
            mRoot = node;
            return true;
        }
        else {
            // move down the root to find the parent of the input node
            return insert(node, *mRoot);
        }
    };


    /**
     * append to output stream
     *
     * @param: out - a reference to output stream to append to
     * @param: tree - a reference to BinaryTreeSameLevelLink to append to
     *
     * @return a reference to ostream appended with values of nodes of this tree, i.e, out
     */
    friend ostream& operator<<(ostream& out, const BinaryTreeSameLevelLink& tree)
    {
        // is tree empty?
        if (NULL == tree.mRoot) {
            return (out << "empty");
        }
        else {
            // traverse down the root to print out values of nodes
            return tree.traverse(out, *tree.mRoot);
        }
    };



protected:


private:


    /**
     *
     * @param: node - to be inserted to the tree
     * @param: parent - to be exmained against the input node
     *
     * @return true if insert is ok
     *
     */
    bool insert(BinaryTreeSameLevelLinkNode* node, BinaryTreeSameLevelLinkNode& parent)
    {
        BinaryTreeSameLevelLinkNode* nextNode = NULL;

        // get pointer to the next node
        if (*node < parent) {
            // input node value is less than the parent value
            nextNode = parent.getLeftPtr();
            if (NULL == nextNode) {
                // no next node, simply set it
                parent.setLeftPtr(node);

                return true;
            }
        }
        else if (*node >= parent) {
            // input node value is greater than or equal to the parent value
            nextNode = parent.getRightPtr();
            if (NULL == nextNode) {
                // no next node, simply set it
                parent.setRightPtr(node);

                return true;
            }
        }

        // move down the tree to find another parent to insert the input node
        return insert(node, *nextNode);
    };


    /**
     *
     * @param: node - to be removed, and all child nodes
     *
     */
    void remove(BinaryTreeSameLevelLinkNode* node)
    {
        // is input null?
        if (NULL == node) return;

        // remove left nodes
        if (NULL != node->getLeftPtr()) {
            remove(node->getLeftPtr());
        }

        // remove right nodes
        if (NULL != node->getRightPtr()) {
            remove(node->getRightPtr());
        }

        // remove the input node
        delete node;
    };


    /**
     * append to value of the input node to output stream and traverse down (depth first) all child nodes
     *
     * @param: out - a reference to output stream to append to
     * @param: node - a reference to BinaryTreeSameLevelLinkNode to append to
     *
     * @return a reference to ostream appended with values of nodes of this tree, i.e., out
     */
    ostream& traverse(ostream& out, BinaryTreeSameLevelLinkNode& node) const
    {
        // append value of the input node to the output stream
        out << node << " ";

        // print out left nodes
        if (NULL != node.getLeftPtr()) {
            out << " L ";
            traverse(out, *node.getLeftPtr());
        }

        // print out right nodes
        if (NULL != node.getRightPtr()) {
            out << " R ";
            traverse(out, *node.getRightPtr());
        }

        return out;
    };


    /**
     * ptr to a BinaryTreeSameLevelLinkNode object
     */
    BinaryTreeSameLevelLinkNode*		mRoot;


};


#endif // __BINARY_TREE_SAME_LEVEL_LINK_HXX_
