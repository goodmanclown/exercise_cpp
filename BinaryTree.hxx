#include "BinaryTreeNode.hxx"

#include <stdint.h>
#include <iostream>

using std::ostream;

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
	BinaryTree():mRoot(NULL) { };

	
	/**
	 * Destructor
	 */
	virtual ~BinaryTree();


	/**
	 *
	 * @param: value - to be inserted to the tree
    *
	 * @return true if insert ok
	 *
	 */
	bool insert(T value);


	/**
	 *
	 * @param: node - to be inserted to the tree
    *
	 */
	bool insert(BinaryTreeNode<T>* node);


	/**
	 *
	 * @param: value - to be removed from the tree.  if there're more than 1 occurrences of value in the tree, the last occurrence is removed
    *
	 * @return true if remove ok.  false if value is not found in the tree
	 *
	 */
	bool remove(T value);


	/**
	 *
	 * @param: value - to be found from the tree.  if there're more than 1 occurrences of value in the tree, the last occurrence is returned
    *
	 * @return BinaryTreeNodePtr if found ok.  NULL if value is not found in the tree
	 *
	 */
	BinaryTreeNode<T>* find(T value);


   /** 
    * append to output stream
    *   
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to BinaryTree to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */  
	friend ostream& operator<<(ostream& out, const BinaryTree<T>& tree);


protected:


private:


	/**
	 *
	 * @param: value - to be inserted to the tree
	 * @param: node - to be exmained against the input value
    *
	 */
	void insert(BinaryTreeNode<T>* value, BinaryTreeNode<T>& node);


	/**
	 *
	 * @param: value - to be removed to the tree
	 * @param: node - to be exmained against the input value
	 * @param: parent - parent of node
    *
	 * @return true if remove ok. false if value is not found in the input node and all linked nodes 
	 *
	 */
	bool remove(T value, BinaryTreeNode<T>* node, BinaryTreeNode<T>& parent);


	/**
	 *
	 * @param: node - to be removed, and all linked nodes
    *
	 */
	void remove(BinaryTreeNode<T>* node);


	/**
	 *
	 * @param: value - to be found in the tree
	 * @param: node - to be exmained against the input value
    *
	 */
	BinaryTreeNode<T>* find(T value, BinaryTreeNode<T>& node);


   /** 
    * append to value of the input node to output stream and traverse down all linked nodes
    *   
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to BinaryTreeNode to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */  
   ostream& traverse(ostream& out, const BinaryTreeNode<T>& node) const;


	/**
	 * ptr to a BinaryTreeNode object
	 */
	BinaryTreeNode<T>*		mRoot;


};


