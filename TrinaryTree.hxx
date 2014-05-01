#include "TrinaryTreeNode.hxx"

#include <stdint.h>
#include <iostream>

using std::ostream;

/**
 * class representing a trinary tree
 *
 * left node has value less than parent
 * middle node has value same as parent
 * right node has value greater than parent
 */ 
class TrinaryTree
{
public:


	/**
    * Constructor
	 */
	TrinaryTree():mRoot(NULL) { };

	
	/**
	 * Destructor
	 */
	virtual ~TrinaryTree();


	/**
	 *
	 * @param: value - to be inserted to the tree
    *
	 * @return true if insert ok
	 *
	 */
	bool insert(uint32_t value);


	/**
	 *
	 * @param: node - to be inserted to the tree
    *
	 */
	bool insert(TrinaryTreeNodePtr node);


	/**
	 *
	 * @param: value - to be removed from the tree.  if there're more than 1 occurrences of value in the tree, the last occurrence is removed
    *
	 * @return true if remove ok.  false if value is not found in the tree
	 *
	 */
	bool remove(uint32_t value);


	/**
	 *
	 * @param: value - to be found from the tree.  if there're more than 1 occurrences of value in the tree, the last occurrence is returned
    *
	 * @return TrinaryTreeNodePtr if found ok.  NULL if value is not found in the tree
	 *
	 */
	TrinaryTreeNodePtr find(uint32_t value);


   /** 
    * append to output stream
    *   
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to TrinaryTree to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */  
	friend ostream& operator<<(ostream& out, const TrinaryTree& tree);


protected:


private:


	/**
	 *
	 * @param: value - to be inserted to the tree
	 * @param: node - to be exmained against the input value
    *
	 */
	void insert(TrinaryTreeNodePtr value, TrinaryTreeNode& node);


	/**
	 *
	 * @param: value - to be removed to the tree
	 * @param: node - to be exmained against the input value
	 * @param: parent - parent of node
    *
	 * @return true if remove ok. false if value is not found in the input node and all linked nodes 
	 *
	 */
	bool remove(uint32_t value, TrinaryTreeNodePtr node, TrinaryTreeNode& parent);


	/**
	 *
	 * @param: node - to be removed, and all linked nodes
    *
	 */
	void remove(TrinaryTreeNodePtr node);


	/**
	 *
	 * @param: value - to be found in the tree
	 * @param: node - to be exmained against the input value
    *
	 */
	TrinaryTreeNodePtr find(uint32_t value, TrinaryTreeNode& node);


   /** 
    * append to value of the input node to output stream and traverse down all linked nodes
    *   
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to TrinaryTreeNode to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */  
   ostream& traverse(ostream& out, const TrinaryTreeNode& node) const;


	/**
	 * ptr to a TrinayTreeNode object
	 */
	TrinaryTreeNode*		mRoot;


};


