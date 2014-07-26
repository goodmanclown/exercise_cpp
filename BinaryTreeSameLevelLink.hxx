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
   void linkSameLevelNode() const
   {
		// is the tree empty	
		if (NULL == mRoot) return;

		// initialize queue to help with the traversal
		ArrayQueue<BinaryTreeSameLevelLinkNode> q(100);

		// insert the root to the queue to kick off the traversal
		q.enqueue(mRoot);

		uint32_t numberOfCurrentLevelNode = 1;
		uint32_t numberOfNextLevelNode = 0;
		BinaryTreeSameLevelLinkNode* sameLevelNode = NULL;

		BinaryTreeSameLevelLinkNode* outNode = NULL;

		// dequeue nodes from the queue until the queue is empty
		while ((outNode = q.dequeue()) != NULL) {

      	// append value of the output node to the output stream
      	std::cout << *outNode << " ";

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

			// check if there's already a list at the same level
			if (sameLevelNode != NULL) {
				// link them together
				sameLevelNode->setSameLevelPtr(outNode);
			}

			// point same level node to this node
			sameLevelNode = outNode;

			// decrement the number of nodes at the current level
			numberOfCurrentLevelNode--;
			if (0 == numberOfCurrentLevelNode) {
				// done with all the nodes at the current level
				numberOfCurrentLevelNode = numberOfNextLevelNode;

	      	std::cout << std::endl << "current " << numberOfCurrentLevelNode << " ";

				numberOfNextLevelNode = 0;
				sameLevelNode = NULL;
			}
		} 	// while ((outNode = q.dequeue()) != NULL) {

		std::cout << std::endl;
   };


   /**
    *
    * @param: node - to be inserted to the tree
    *
    * @return true if insert is ok
    *
    */
   bool insert(BinaryTreeSameLevelLinkNode* node)
   {
		// if the input is NULL, just return
      if (NULL == node) return false;

      if (mRoot == NULL) {
         // no node yet
         // just add it to the root
         mRoot = node;
         return true;
      }
      else {
         // move down the root to find a node to insert the input value
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
    * @param: value - to be inserted to the tree
    * @param: node - to be exmained against the input value
	 *
    * @return true if insert is ok
    *
    */
   bool insert(BinaryTreeSameLevelLinkNode* value, BinaryTreeSameLevelLinkNode& node)
   {
      // get pointer to the next node
      BinaryTreeSameLevelLinkNode* nextNode = NULL;

		if (value->getValue() < node.getValue()) {
			// input value is less than the node value
			nextNode = node.getLeftPtr();
      	if (NULL == nextNode) {
        		// no next node, simply set it
         	node.setLeftPtr(value);

				return true;
      	}
		}
		else if (value->getValue() >= node.getValue()) {
			// input value is greater than or equal to the node value
			nextNode = node.getRightPtr();
      	if (NULL == nextNode) {
        		// no next node, simply set it
         	node.setRightPtr(value);

				return true;
			}
		}

      // move down the node to find another node to insert the input value
      return insert(value, *nextNode);
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
