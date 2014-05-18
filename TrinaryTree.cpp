#include "TrinaryTree.hxx"

using namespace std;

TrinaryTree::~TrinaryTree()
{	
	// remove all nodes 
	remove(mRoot);

	mRoot = NULL;
}


bool TrinaryTree::insert(uint32_t value)
{
	TrinaryTreeNodePtr node = new (nothrow) TrinaryTreeNode(value);

	return insert(node);
}


bool TrinaryTree::insert(TrinaryTreeNodePtr node)
{
	// is new ok? 
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
}

		
void TrinaryTree::insert(TrinaryTreeNodePtr value, TrinaryTreeNode& node)
{	
	// get pointer to the next node
	TrinaryTreeNodePtr nextNode = node.getPtr(*value);

	if (NULL == nextNode) {
		// no next node, simply set it
		node.setPtr(value);
	}
	else {
		// move down the node to find another node to insert the input value
		insert(value, *nextNode);
	}
}


bool TrinaryTree::remove(uint32_t value)
{
	// is tree empty?
	if (NULL == mRoot) return false;

	if (*mRoot > value && NULL != mRoot->getLessThanPtr()) {
		// move down the less than path
		return remove(value, mRoot->getLessThanPtr(), *mRoot);
	}
	else if (*mRoot < value && NULL != mRoot->getGreaterThanPtr()) {
		// move down the greater than path
		return remove(value, mRoot->getGreaterThanPtr(), *mRoot);
	}
	else if (*mRoot == value) {
		if (NULL != mRoot->getEqualToPtr()) {
			// move down the equal to path
			return remove(value, mRoot->getEqualToPtr(), *mRoot);
		}
		else {
			// to remove the mRoot

			TrinaryTreeNodePtr gtnode = mRoot->getGreaterThanPtr();
			TrinaryTreeNodePtr ltnode = mRoot->getLessThanPtr();
	
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
		}
	} 	// else if (*mRoot == value) {
	
	return false;
}


bool TrinaryTree::remove(uint32_t value, TrinaryTreeNodePtr node, TrinaryTreeNode& parent)
{	
	// get pointer to the next node
	TrinaryTreeNodePtr nextNode = node->getPtr(value);

	if (NULL == nextNode) {
		// no next node
		if (*node == value) {
			// so we are at the last ocurrence of the value
	
			// remove this node from parent first
			parent.remove(*node);

			TrinaryTreeNodePtr gtnode = node->getGreaterThanPtr();
			TrinaryTreeNodePtr ltnode = node->getLessThanPtr();
	
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
}


void TrinaryTree::remove(TrinaryTreeNodePtr node) 
{
	// is input null? 
	if (NULL == node) return;

	// remove less than nodes
	if (NULL != node->getLessThanPtr()) {
		remove(node->getLessThanPtr());
	}
	
	// remove euqal to nodes 
	if (NULL != node->getEqualToPtr()) {
		remove(node->getEqualToPtr());
	}

	// remove greater than nodes 
	if (NULL != node->getGreaterThanPtr()) {
		remove(node->getGreaterThanPtr());
	}

	// remove the input node
	delete node;
}

ostream& TrinaryTree::traverse(ostream& out, const TrinaryTreeNode& node) const
{
	// append value of the input node to the output stream
	out << node << " ";

	// print out less than nodes
	if (NULL != node.getLessThanPtr()) {
		traverse(out, *node.getLessThanPtr());
	}
	
	// print out euqal to nodes 
	if (NULL != node.getEqualToPtr()) {
		traverse(out, *node.getEqualToPtr());
	}

	// print out greater than nodes 
	if (NULL != node.getGreaterThanPtr()) {
		traverse(out, *node.getGreaterThanPtr());
	}

	return out;
}


TrinaryTreeNodePtr TrinaryTree::find(uint32_t value)
{
	if (NULL == mRoot) {
		// no node yet
		// just add it to the root
		return NULL;
	}

	// move down the root to find a node that matches the input value
	return find(value, *mRoot);
}


TrinaryTreeNodePtr TrinaryTree::find(uint32_t value, TrinaryTreeNode& node)
{
	// if the input node has the same value	
	if (node.getValue() == value) return &node;
	else {
		// get pointer to the next node
		TrinaryTreeNodePtr nextNode = node.getPtr(value);

		if (NULL != nextNode) {
			// move down the node to find another node that matches the input value
			return find(value, *nextNode);
		}

		// no next node, the input value is not in the tree
		return NULL;
	}
}


ostream& operator<<(ostream& out, const TrinaryTree& tree)
{
	// is tree empty?
	if (NULL == tree.mRoot) {
		return (out << "empty");
	}
	else {
		// traverse down the root to print out values of nodes
		return tree.traverse(out, *tree.mRoot);
	}
}


