#pragma once

#include "BinaryTreeNode.hxx"

#include <stdint.h>
#include <functional>
#include <iostream>
#include <vector>

using std::ostream;
using std::vector;

/**
 * class representing a binary search tree
 *
 * left node has value less than parent
 * right node has value greater than parent
 */
template<typename T>
class BinarySearchTree
{
public:


   /**
    * Constructor
    */
   BinarySearchTree() = default;


   /**
    * Constructor
    */
   BinarySearchTree(const T sortedArray[], std::size_t len)
   {
      mRoot = populate(sortedArray, len);
   };



   /**
    * Destructor
    */
   virtual ~BinarySearchTree() = default;


   /**
    *
    * @param: value - to be inserted to the tree
    *
    * @return true if insert ok
    *
    */
   bool insert(T value)
   {
      BinaryTreeNodePtr<T> node = std::make_shared<BinaryTreeNode<T>>(value);

      return insert(node);
   };



   /**
    *
    * @param: node - to be inserted to the tree
    *
    */
   bool insert(BinaryTreeNodePtr<T> node)
   {
      // is new ok?
      if (nullptr == node) return false;

      if (nullptr == mRoot) {
         // no node yet
         // just add it to the root
         mRoot.swap(node);
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
    * @param: value - to be removed from the tree.  if there're more than 1 occurrences of value in the tree, the last occurrence is removed
    *
    * @return true if remove ok.  false if value is not found in the tree
    *
    */
   bool remove(T value)
   {
      // is tree empty?
      if (nullptr == mRoot) return false;

      if (*mRoot > value && nullptr != mRoot->getLessThanPtr()) {
         // move down the less than path
         return remove(value, mRoot->getLessThanPtr(), *mRoot);
      }
      else if (*mRoot < value && nullptr != mRoot->getGreaterThanEqualToPtr()) {
         // move down the greater than path
         return remove(value, mRoot->getGreaterThanEqualToPtr(), *mRoot);
      }
      else if (*mRoot == value) {
         // to remove the mRoot

         BinaryTreeNodePtr<T> gtnode = mRoot->getGreaterThanEqualToPtr();
         BinaryTreeNodePtr<T> ltnode = mRoot->getLessThanPtr();

         if (nullptr != gtnode) {
            if (nullptr != ltnode) {
               // first insert the less than node to the greater than node
               insert(ltnode, *gtnode);

               // set greater than node as root
               mRoot.swap(gtnode);
               return true;
            }
            else {
               // no less than node
               // set greater than as root
               mRoot.swap(gtnode);
               return true;
            }
         }
         else if (nullptr != ltnode) {
            // no greater than node
            // set less than as root
            mRoot.swap(ltnode);
            return true;
         }
         else {
            // a single node
            // just delete it
            mRoot.reset();
            return true;
         }
      } 	// else if (*mRoot == value) {

      return false;
   }


   /**
    *
    * @param: value - to be found from the tree.  if there're more than 1 occurrences of value in the tree, the last occurrence is returned
    *
    * @return BinaryTreeNodePtr if found ok.  NULL if value is not found in the tree
    *
    */
   BinaryTreeNodePtr<T> find(T value) const
   {
      if (nullptr == mRoot) {
         // no node yet
         return nullptr;
      }

      // move down the root to find a node that matches the input value
      return find(std::bind(mDefaultCompFunc, value, std::placeholders::_1), 
            mRoot, 
            std::bind(mPreOrderTraversalFunc, value, std::placeholders::_1));
   };


   /**
    *
    * @param: value - to be found from the tree.  if there're more than 1 occurrences of value in the tree, the last occurrence is returned
    * @param: compFunc - comparison functoin to be used in finding value
    *
    * @return BinaryTreeNodePtr if found ok.  NULL if value is not found in the tree
    *
    */
   BinaryTreeNodePtr<T> find(std::function<bool(const T&)> compFunc, 
                           std::function<bool(const T&)> preOrderTraversalFunc) const
   {
      if (nullptr == mRoot) {
         // no node yet
         return nullptr;
      }

      // move down the root to find a node that matches the input value
      return find(compFunc, mRoot, preOrderTraversalFunc);
   };


   /**
    * append to output stream
    *
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to BinaryTree to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */
   friend ostream& operator<<(ostream& out, const BinarySearchTree<T>& tree)
   {
      // is tree empty?
      if (nullptr == tree.mRoot) {
         return (out << "empty");
      }
      else {
         // traverse down the root to print out values of nodes
         return tree.traverse(out, *tree.mRoot);
      }
   };


   /**
    * append to value of this tree pre-order
    *
    * @param: out - a reference to output stream to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traverse(ostream& out) const
   {
      if (nullptr == mRoot) return out;

      return traverse(out, *mRoot);
   }


   /**
    * append to value of this tree in-order
    *
    * @param: out - a reference to output stream to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traverseInOrder(ostream& out) const
   {
      if (nullptr == mRoot) return out;

      return traverseInOrder(out, *mRoot);
   }


   /**
    * append to value of this tree post-order
    *
    * @param: out - a reference to output stream to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traversePostOrder(ostream& out) const
   {
      if (nullptr == mRoot) return out;

      return traversePostOrder(out, *mRoot);
   }


   /**
    *
    * @return true if tree is in order
    */
   bool isInOrder() const
   {
      if (nullptr == mRoot) return false;

      return isInOrder(*mRoot);
   }


protected:


private:


   /**
    *
    * @param: value - to be inserted to the tree
    * @param: node - to be exmained against the input value
    *
    */
   void insert(BinaryTreeNodePtr<T> value, BinaryTreeNode<T>& node)
   {
		std::cout << "insert value " << value->getValue() << ", node " << node.getValue() << std::endl;

      // if the value to be inserted is same as the node, just return
      if (*value == node) return;

      if (*value < node) 
      {
		std::cout << "insert L" << std::endl;

         auto nextNode = node.getLessThanPtr();
         if (nextNode == nullptr)
         {
            node.setLessThanPtr(value);
         }
         else
         {
            // move down the node to find another node to insert the input value
            insert(value, *nextNode);
         }
      }
      else
      {
		std::cout << "insert R" << std::endl;

         auto nextNode = node.getGreaterThanEqualToPtr();
         if (nextNode == nullptr)
         {
            node.setGreaterThanEqualToPtr(value);
         }
         else
         {
            // move down the node to find another node to insert the input value
            insert(value, *nextNode);
         }
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
   bool remove(T value, BinaryTreeNodePtr<T> node, BinaryTreeNode<T>& parent)
   {
      if (*node == value) {
         // so we are at the first ocurrence of the value

         // remove this node from parent first
         parent.remove(*node);

         BinaryTreeNodePtr<T> gtnode = node->getGreaterThanEqualToPtr();
         BinaryTreeNodePtr<T> ltnode = node->getLessThanPtr();

         if (nullptr != gtnode) {
            if (nullptr != ltnode) {
               // first insert the less than node to the greater than node
               insert(ltnode, *gtnode);

               // set the greater than node to parent
               node.reset();
               parent.setPtr(gtnode);
               return true;
            }
            else {
               // no less than node
               // set greater than node to parent
               node.reset();
               parent.setPtr(gtnode);
               return true;
            }
         }
         else if (nullptr != ltnode) {
            // no greater than node
            // set less than node to parent
            node.reset();
            parent.setPtr(ltnode);
            return true;
         }
         else {
            // a single node
            // just delete it
            node.reset();
            return true;
         }
      }	// if (value == *node) {
      else {
         // get pointer to the next node
         BinaryTreeNodePtr<T> nextNode = node->getPtr(value);

         if (nullptr != nextNode) {
            // move down the next node
            return remove(value, nextNode, *node);
         }
      }

      return false;
   };


   /**
    *
    * @param: value - to be found in the tree
    * @param: node - to be exmained against the input value
    *
    */
   BinaryTreeNodePtr<T> find(std::function<bool(const T&)> compFunc, 
                              BinaryTreeNodePtr<T> node, 
                              std::function<bool(const T&)> preOrderTraversalFunc) const
   {
		std::cout << "find " << node->getValue() << " L " << node->getLessThanPtr().get() << " R " << node->getGreaterThanEqualToPtr().get() << std::endl;

      // if the input node has the same value
      if (compFunc(node->getValue()) == true) return node;
      else {
         if (preOrderTraversalFunc(node->getValue()) == true) {
            const auto nextNode = node->getLessThanPtr();

            if (nextNode != nullptr) {

		std::cout << "find L " << nextNode->getValue() << std::endl;

               // move down the node to find another node that matches the input value
               return find(compFunc, nextNode, preOrderTraversalFunc);
            }
         }
         else {
            const auto nextNode = node->getGreaterThanEqualToPtr();

            if (nullptr != nextNode) {

		std::cout << "find R " << nextNode->getValue() << std::endl;

               // move down the node to find another node that matches the input value
               return find(compFunc, nextNode, preOrderTraversalFunc);
            }
         }
      }
      return nullptr;
   };


   /**
    *
    * @param: node - a reference to BinaryTreeNode to examine
    *
    * @return true if tree is in order
    */
   bool isInOrder(const BinaryTreeNode<T>& node) const
   {
      // go down the left node
      if (nullptr != node.getLessThanPtr()) 
      {
         if (*node.getLessThanPtr() > node) return false;
         
         bool ret = isInOrder(*node.getLessThanPtr());

         if (ret == false) return false;
      }

      // go down the right node
      if (nullptr != node.getGreaterThanEqualToPtr()) 
      {
         if (*node.getGreaterThanEqualToPtr() < node) return false;

         bool ret = isInOrder(*node.getGreaterThanEqualToPtr());

         if (ret == false) return false;
      }

      return true;
   };


   /**
    * append to value of the input node to output stream and pre-order traverse down all linked nodes
    *
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to BinaryTreeNode to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traverse(ostream& out, const BinaryTreeNode<T>& node) const
   {
      // append value of the input node to the output stream
      out << node << " ";

      // print out less than nodes
      if (nullptr != node.getLessThanPtr()) {
         traverse(out, *node.getLessThanPtr());
      }

      // print out greater than nodes
      if (nullptr != node.getGreaterThanEqualToPtr()) {
         traverse(out, *node.getGreaterThanEqualToPtr());
      }

      return out;
   };


   /**
    * append to value of the input node to output stream and in order traverse down all linked nodes
    *
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to BinaryTreeNode to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traverseInOrder(ostream& out, const BinaryTreeNode<T>& node) const
   {
      // go down the left node
      // print out less than nodes
      if (nullptr != node.getLessThanPtr()) 
      {
         traverseInOrder(out, *node.getLessThanPtr());
      }

      // append value of the current node to the output stream
      out << node << " ";

      // print out greater than nodes
      if (nullptr != node.getGreaterThanEqualToPtr()) 
      {
         traverseInOrder(out, *node.getGreaterThanEqualToPtr());
      }

      return out;
   };


   /**
    * append to value of the input node to output stream and post order traverse down all linked nodes
    *
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to BinaryTreeNode to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traversePostOrder(ostream& out, const BinaryTreeNode<T>& node) const
   {
      // go down the left node
      // print out less than nodes
      if (nullptr != node.getLessThanPtr()) 
      {
         traversePostOrder(out, *node.getLessThanPtr());
      }

      // print out greater than nodes
      if (nullptr != node.getGreaterThanEqualToPtr()) 
      {
         traversePostOrder(out, *node.getGreaterThanEqualToPtr());
      }

      // append value of the current node to the output stream
      out << node << " ";

      return out;
   };


   /**
    * populate - recursive
    */
   BinaryTreeNodePtr<T> populate(const T pArray[], std::size_t pArraySize)
   {
       if (pArraySize == 0) return nullptr;

       if (pArraySize == 1)
       {  // just 1 element
          std::cout << "populate: " << pArray[0] << std::endl;
          return std::make_shared<BinaryTreeNode<T>>(pArray[0]);
       }

       // divide the array into 2 half
       std::size_t midIndex = pArraySize / 2;
     
       std::cout << "populate: " << pArray[midIndex] << std::endl;
       auto node = std::make_shared<BinaryTreeNode<T>>(pArray[midIndex]);
      
       // populate the 1st half to the left of root
       if (midIndex >= 1)
       {
          node->setPtr(populate(pArray, midIndex));
       }

       // populate the 2nd half to the right of root
       if (pArraySize-midIndex-1 > 0)
       {
          node->setPtr(populate(&pArray[midIndex+1], pArraySize-midIndex-1));
       }

       return node;
   };


   /**
    * ptr to a BinaryTreeNode object
    */
   BinaryTreeNodePtr<T>		mRoot;


   /**
    * default comparison function for the find API
    */
   std::function<bool(const T&, const T&)> mDefaultCompFunc = std::equal_to<T>();

   /**
    * default preorder traversal function for the find API
    */
   std::function<bool(const T&, const T&)> mPreOrderTraversalFunc = std::less<T>();

};


