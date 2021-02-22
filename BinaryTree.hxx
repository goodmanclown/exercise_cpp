#pragma once

#include "BinaryTreeNode.hxx"

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using std::accumulate;
using std::ostream;
using std::vector;

/**
 * class representing a binary tree
 *
 * left node has value less than parent
 * right node has value greater than parent
 */
template<typename T>
class BinaryTree
{
public:


   /**
    * Constructor
    */
   BinaryTree() = default;


   /**
    * Destructor
    */
   virtual ~BinaryTree() = default;



   /**
    *
    * @param: value - to be inserted to the tree
    *
    * @return true if insert ok
    *
    */
   bool insert(T value)
   {
      BinaryTreeNodePtr<T> node(new (std::nothrow) BinaryTreeNode<T>(value));

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
   BinaryTreeNodePtr<T> find(T value)
   {
      if (nullptr == mRoot) {
         // no node yet
         return nullptr;
      }

      // move down the root to find a node that matches the input value
      return find(value, mRoot);
   };


   T traverseAndSum() const
   {
      if (mRoot == nullptr) return 0;

      vector<T> vLeafNodeValue;

      traverseAndSum(*(mRoot), 0, vLeafNodeValue); 

      auto sum = accumulate(vLeafNodeValue.cbegin(), vLeafNodeValue.cend(), 0);

      return sum;
   }

   /**
    * append to output stream
    *
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to BinaryTree to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */
   friend ostream& operator<<(ostream& out, const BinaryTree<T>& tree)
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
      // get pointer to the next node
      BinaryTreeNodePtr<T> nextNode = node.getPtr(*value);

      if (nullptr == nextNode) {
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
   bool remove(T value, BinaryTreeNodePtr<T> node, BinaryTreeNode<T>& parent)
   {
      if (*node == value) {
         // so we are at the last ocurrence of the value

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
    * @param: node - to be removed, and all linked nodes
    *
    */
   void remove(BinaryTreeNodePtr<T> node)
   {
      // is input null?
      if (nullptr == node) return;

      // remove less than nodes
      if (nullptr != node->getLessThanPtr()) {
         remove(node->getLessThanPtr());
      }

      // remove greater than nodes
      if (nullptr != node->getGreaterThanEqualToPtr()) {
         remove(node->getGreaterThanEqualToPtr());
      }

      // remove the input node
      node.reset();
   };


   /**
    *
    * @param: value - to be found in the tree
    * @param: node - to be exmained against the input value
    *
    */
   BinaryTreeNodePtr<T> find(T value, BinaryTreeNodePtr<T> node)
   {
      std::cout << "find " << value << ", " << node->getValue() << std::endl;

      // if the input node has the same value
      if (node->getValue() == value) return node;
      else {
         // get pointer to the next node
         auto nextNode = node->getPtr(value);

         if (nullptr != nextNode) {
            // move down the node to find another node that matches the input value
            return find(value, nextNode);
         }

         // no next node, the input value is not in the tree
         return nullptr;
      }
   };

   void traverseAndSum(const BinaryTreeNode<T>& node, const T prefix, vector<T>& vLeafNodeValue) const
   {
       auto newPrefix = prefix * 10 + node.getValue();

       if (node.getLessThanPtr() == nullptr && node.getGreaterThanEqualToPtr() == nullptr)
       {
          vLeafNodeValue.emplace_back(newPrefix);
       }

       if (node.getLessThanPtr() != nullptr)
       {
           traverseAndSum(*(node.getLessThanPtr()), newPrefix, vLeafNodeValue);
       }

       if (node.getGreaterThanEqualToPtr() != nullptr)
       {
           traverseAndSum(*(node.getGreaterThanEqualToPtr()), newPrefix, vLeafNodeValue);
       }
   }

   /**
    * append to value of the input node to output stream and traverse down all linked nodes
    * in pre-order
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
      	out << "L ";
        traverse(out, *(node.getLessThanPtr()));
      }

      // print out greater than nodes
      if (nullptr != node.getGreaterThanEqualToPtr()) {
        out << "R ";
        traverse(out, *(node.getGreaterThanEqualToPtr()));
      }

      return out;
   };

   /**
    * append to value of the input node to output stream and traverse down all linked nodes
    * in In-order
    *
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to BinaryTreeNode to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traverseInOrder(ostream& out, const BinaryTreeNode<T>& node) const
   {
      // print out less than nodes
      if (nullptr != node.getLessThanPtr()) {
        out << "L ";
        traverseInOrder(out, *(node.getLessThanPtr()));
      }

      // append value of the input node to the output stream
      out << node << " ";

      // print out greater than nodes
      if (nullptr != node.getGreaterThanEqualToPtr()) {
      	out << "R ";
        traverseInOrder(out, *(node.getGreaterThanEqualToPtr()));
      }

      return out;
   };

   /**
    * append to value of the input node to output stream and traverse down all linked nodes
    * in post-order
    *
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to BinaryTreeNode to append to
    *
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */
   ostream& traversePostOrder(ostream& out, const BinaryTreeNode<T>& node) const
   {
      // print out less than nodes
      if (nullptr != node.getLessThanPtr()) {
      	out << "L ";
        traversePostOrder(out, *(node.getLessThanPtr()));
      }

      // print out greater than nodes
      if (nullptr != node.getGreaterThanEqualToPtr()) {
      	out << "R ";
        traversePostOrder(out, *(node.getGreaterThanEqualToPtr()));
      }

      // append value of the input node to the output stream
      out << node << " ";

      return out;
   };

   /**
    * ptr to a BinaryTreeNode object
    */
   BinaryTreeNodePtr<T>		mRoot;


};


