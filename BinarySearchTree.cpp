#include "BinaryTree.hxx"

using namespace std;

template<typename T>
BinaryTree<T>::~BinaryTree()
{	
	// remove all nodes 
	remove(mRoot);

	mRoot = NULL;
}


template<typename T>
bool BinaryTree<T>::insert(T value)
{
	BinaryTreeNode<T>* node = new (nothrow) BinaryTreeNode<T>(value);

	return insert(node);
}


template<typename T>
bool BinaryTree<T>::insert(BinaryTreeNode<T>* node)
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

		
template<typename T>
void BinaryTree<T>::insert(BinaryTreeNode<T>* value, BinaryTreeNode<T>& node)
{
	// if the value to be inserted is same as the node, just return
	if (value->getValue() == node.getValue()) return;
	
	// get pointer to the next node
	BinaryTreeNode<T>* nextNode = node.getPtr(*value);

	if (NULL == nextNode) {
		// no next node, simply set it
		node.setPtr(value);
	}
	else {
		// move down the node to find another node to insert the input value
		insert(value, *nextNode);
	}
}


template<typename T>
bool BinaryTree<T>::remove(T value)
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
		// to remove the mRoot

		BinaryTreeNode<T>* gtnode = mRoot->getGreaterThanPtr();
		BinaryTreeNode<T>* ltnode = mRoot->getLessThanPtr();
	
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


template<typename T>
bool BinaryTree<T>::remove(T value, BinaryTreeNode<T>* node, BinaryTreeNode<T>& parent)
{	
	// get pointer to the next node
	BinaryTreeNode<T>* nextNode = node->getPtr(value);

	if (NULL == nextNode) {
		// no next node
		if (*node == value) {
			// so we are at the last ocurrence of the value
	
			// remove this node from parent first
			parent.remove(*node);

			BinaryTreeNode<T>* gtnode = node->getGreaterThanPtr();
			BinaryTreeNode<T>* ltnode = node->getLessThanPtr();
	
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


template<typename T>
void BinaryTree<T>::remove(BinaryTreeNode<T>* node) 
{
	// is input null? 
	if (NULL == node) return;

	// remove less than nodes
	if (NULL != node->getLessThanPtr()) {
		remove(node->getLessThanPtr());
	}
	
	// remove greater than nodes 
	if (NULL != node->getGreaterThanPtr()) {
		remove(node->getGreaterThanPtr());
	}

	// remove the input node
	delete node;
}


template<typename T>
ostream& BinaryTree<T>::traverse(ostream& out, const BinaryTreeNode<T>& node) const
{
	// append value of the input node to the output stream
	out << node << " ";

	// print out less than nodes
	if (NULL != node.getLessThanPtr()) {
		traverse(out, *node.getLessThanPtr());
	}
	
	// print out greater than nodes 
	if (NULL != node.getGreaterThanPtr()) {
		traverse(out, *node.getGreaterThanPtr());
	}

	return out;
}


template<typename T>
BinaryTreeNodePtr BinaryTree<T>::find(T value)
{
	if (NULL == mRoot) {
		// no node yet
		return NULL;
	}

	// move down the root to find a node that matches the input value
	return find(value, *mRoot);
}


template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::find(T value, BinaryTreeNode<T>& node)
{
	// if the input node has the same value	
	if (node.getValue() == value) return &node;
	else {
		// get pointer to the next node
		BinaryTreeNode<T>* nextNode = node.getPtr(value);

		if (NULL != nextNode) {
			// move down the node to find another node that matches the input value
			find(value, *nextNode);
		}

		// no next node, the input value is not in the tree
		return NULL;
	}
}


ostream& operator<<(ostream& out, const BinaryTree<T>& tree)
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


