#ifndef __BINARY_TREE_SAME_LEVEL_LINK_HXX_
#define __BINARY_TREE_SAME_LEVEL_LINK_HXX_

#include "BinaryTreeSameLevelLinkNode.hxx"

#include <stdint.h>
#include <iostream>

using std::ostream;


/**
 * class representing a binary tree
 *
 * left node has value less than parent
 * right node has value greater than parent
 *
 * each node has a link to the same level node on its right
 */
template<typename T>
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
    * @param: value - to be inserted to the tree
    *
    * @return true if insert ok
    *
    */
   bool insert(T value)
   {
		BinaryTreeSameLevelLinkNode<T>* node = new (std::nothrow) BinaryTreeSameLevelLinkNode<T>(value);

      return insert(node);
   };



   /**
    *
    * @param: node - to be inserted to the tree
    *
    */
   bool insert(BinaryTreeSameLevelLinkNode<T>* node)
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
         // move down the root to find a node to insert the input value
         insert(node, *mRoot);
         return true;
      }

      return false;
   };



   /**
    *
    * @param: value - to be removed from the tree.  if there's duplicate, the 2nd instance will be removed first
    *
    * @return true if remove ok.  false if value is not found in the tree
    *
    */
   bool remove(T value)
   {
      // is tree empty?
      if (NULL == mRoot) return false;

      if ((*mRoot >= value) && (NULL != mRoot->getLessThanPtr())) {
         // move down the less than path
         return remove(value, mRoot->getLessThanPtr(), *mRoot);
      }
      else if ((*mRoot < value) && (NULL != mRoot->getGreaterThanEqualToPtr())) {
         // move down the greater than or equal to path
         return remove(value, mRoot->getGreaterThanEqualToPtr(), *mRoot);
      }
      else if (*mRoot == value) {
         // to remove the mRoot

         BinaryTreeSameLevelLinkNode<T>* gtnode = mRoot->getGreaterThanEqualToPtr();
         BinaryTreeSameLevelLinkNode<T>* ltnode = mRoot->getLessThanPtr();

         if (NULL != gtnode) {
            if (NULL != ltnode) {
               // first insert the less than node to the greater than node
               insert(ltnode, *gtnode);

               // set greater than node as root
               delete mRoot;
               mRoot = gtnode;
               return true;
            }
            else {
               // no less than node
               // set greater than as root
               delete mRoot;
               mRoot = gtnode;
               return true;
            }
         }
         else if (NULL != ltnode) {
            // no greater than node
            // set less than as root
            delete mRoot;
            mRoot = ltnode;
            return true;
         }
         else {
            // a single node
            // just delete it
            delete mRoot;
            mRoot = NULL;
            return true;
         }
      } 	// else if (*mRoot == value) {

      return false;
   }


   /**
    * append to output stream
    *
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to BinaryTreeSameLevelLink to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */
   friend ostream& operator<<(ostream& out, const BinaryTreeSameLevelLink<T>& tree)
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
    */
   void insert(BinaryTreeSameLevelLinkNode<T>* value, BinaryTreeSameLevelLinkNode<T>& node)
   {
      // get pointer to the next node
      BinaryTreeSameLevelLinkNode<T>* nextNode = node.getPtr(*value);

      if (NULL == nextNode) {
         // no next node, simply set it
         node.setPtr(value);
      }
      else {
         // move down the node to find another node to insert the input value
         insert(value, *nextNode);
      }
   };


   /**
    *
    * @param: value - to be removed to the tree
    * @param: node - to be exmained against the input value
    * @param: parent - parent of node
    *
    * @return true if remove ok. false if value is not found in the input node and all linked nodes
    *
    */
   bool remove(T value, BinaryTreeSameLevelLinkNode<T>* node, BinaryTreeSameLevelLinkNode<T>& parent)
   {
      // get pointer to the next node
      BinaryTreeSameLevelLinkNode<T>* nextNode = node->getPtr(value);

      if (NULL == nextNode) {
         // no next node
         if (*node == value) {
            // remove this node from parent first
            parent.remove(*node);

            BinaryTreeSameLevelLinkNode<T>* gtnode = node->getGreaterThanEqualToPtr();
            BinaryTreeSameLevelLinkNode<T>* ltnode = node->getLessThanPtr();

            if (NULL != gtnode) {
               if (NULL != ltnode) {
                  // first insert the less than node to the greater than node
                  insert(ltnode, *gtnode);

                  // set the greater than node to parent
                  delete node;
                  parent.setPtr(gtnode);
                  return true;
               }
               else {
                  // no less than node
                  // set greater than node to parent
                  delete node;
                  parent.setPtr(gtnode);
                  return true;
               }
            }
            else if (NULL != ltnode) {
               // no greater than node
               // set less than node to parent
               delete node;
               parent.setPtr(ltnode);
               return true;
            }
            else {
               // a single node
               // just delete it
               delete node;
               return true;
            }
         }	// if (value == *node) {
         else {
            // no more node to examine and we can't find a node matching the input value
            return false;
         }
      }
      else {
         // move down the next node
         return remove(value, nextNode, *node);
      }

      return false;
   };


   /**
    *
    * @param: node - to be removed, and all linked nodes
    *
    */
   void remove(BinaryTreeSameLevelLinkNode<T>* node)
   {
      // is input null?
      if (NULL == node) return;

      // remove less than nodes
      if (NULL != node->getLessThanPtr()) {
         remove(node->getLessThanPtr());
      }

      // remove greater than nodes
      if (NULL != node->getGreaterThanEqualToPtr()) {
         remove(node->getGreaterThanEqualToPtr());
      }

      // remove the input node
      delete node;
   };


   /**
    * append to value of the input node to output stream and traverse down all linked nodes
    *
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to BinaryTreeSameLevelLinkNode to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traverse(ostream& out, const BinaryTreeSameLevelLinkNode<T>& node) const
   {
      // append value of the input node to the output stream
      out << node << " ";

      // print out less than nodes
      if (NULL != node.getLessThanPtr()) {
      	out << "L ";
         traverse(out, *node.getLessThanPtr());
      }

      // print out greater than nodes
      if (NULL != node.getGreaterThanEqualToPtr()) {
      	out << "R ";
         traverse(out, *node.getGreaterThanEqualToPtr());
      }

      return out;
   };


   /**
    * ptr to a BinaryTreeSameLevelLinkNode object
    */
   BinaryTreeSameLevelLinkNode<T>*		mRoot;


};


#endif // __BINARY_TREE_SAME_LEVEL_LINK_HXX_
