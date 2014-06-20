#include "SingLinkedList.hxx"

using namespace std;

SingLinkedList::SingLinkedList(SingLinkedList& rhs):mHead(NULL),mLength(rhs.mLength)
{
	if (0 < rhs.mLength) {
		// make sure we have something to copy
		mHead = new SingLinkedListNode(rhs.mHead->getValue());
		
		SingLinkedListNodePtr currentNode = mHead;
		SingLinkedListNodePtr rhsNode = rhs.mHead->getNextPtr();

		for (uint32_t index=1; index < rhs.mLength && rhsNode != NULL; index++) {
			
			// make a copy of the rhsNode and append it to the currentNode
			currentNode->setNextPtr(new SingLinkedListNode(rhsNode->getValue()));

			// move down to copy next node
			currentNode = currentNode->getNextPtr();
			rhsNode = rhsNode->getNextPtr();
		}
	} 
}


SingLinkedList::~SingLinkedList()
{
	// remove all nodes 
	SingLinkedListNodePtr currentNode = mHead;
	SingLinkedListNodePtr nextNode = NULL;
	// move to the node at the pos
	while (currentNode != NULL) {
		nextNode = currentNode->getNextPtr();
		delete currentNode;
		currentNode = nextNode;
	}	

	mHead = NULL;
}


SingLinkedList& SingLinkedList::operator=(SingLinkedList& rhs)
{
	if (this == &rhs) return *this;

	mHead = NULL;
	mLength = rhs.mLength;

	if (0 < rhs.mLength) {
		// make sure we have something to copy
		mHead = new SingLinkedListNode(rhs.mHead->getValue());

		SingLinkedListNodePtr currentNode = mHead;
		SingLinkedListNodePtr rhsNode = rhs.mHead->getNextPtr();

		for (uint32_t index=1; index < rhs.mLength && rhsNode != NULL; index++) {
			
			// make a copy of the rhsNode and append it to the currentNode
			currentNode->setNextPtr(new SingLinkedListNode(rhsNode->getValue()));

			// move down to copy next node
			currentNode = currentNode->getNextPtr();
			rhsNode = rhsNode->getNextPtr();
		}
	} 

	return *this;
}


bool SingLinkedList::operator==(SingLinkedList& rhs)
{
	// return false if length is different
	if (mLength != rhs.mLength) return false;

	if (0 < mLength) {
		// make sure we have something to compare
		SingLinkedListNodePtr currentNode = mHead;
		SingLinkedListNodePtr rhsNode = rhs.mHead;

		for (uint32_t index=0; index < mLength && currentNode != NULL && rhsNode != NULL; index++) {
			
			// compare the value of these 2 nodes
			if (currentNode->getValue() != rhsNode->getValue()) return false;

			// move down to copy next node
			currentNode = currentNode->getNextPtr();
			rhsNode = rhsNode->getNextPtr();
		}
	} 

	return true;
}


SingLinkedListNodePtr SingLinkedList::pop_front()
{
	// is there any node to pop
	if (0 == mLength) return NULL;

	SingLinkedListNodePtr nextNode = mHead->getNextPtr();

	SingLinkedListNodePtr node = mHead;

	mHead = nextNode;

	mLength--;

	return node;
}


bool SingLinkedList::insert(uint32_t value, uint32_t pos)
{
	SingLinkedListNodePtr node = new (nothrow) SingLinkedListNode(value);

	// is new ok? 
	if (NULL == node) return false;

	if (NULL == mHead && 0 != pos) return false;

	if (0 == pos) {
		// just add it to the head
		node->setNextPtr(mHead);
		mHead = node;
		mLength++;
		return true;
	}
	else {
		SingLinkedListNodePtr currentNode = mHead;
		SingLinkedListNodePtr nextNode = NULL;
		// move to the node just before the pos
		for (uint32_t count = pos - 1; count > 0 && currentNode != NULL; count--) {
			nextNode = currentNode->getNextPtr();
			currentNode = nextNode;
		}
		if (currentNode != NULL) {
			// insert the new node between currentNode and its nextNode
			currentNode->insert(node);
			mLength++;
			return true;
		}
	}

	return false;
}

		
bool SingLinkedList::insert(SingLinkedListNodePtr node)
{
	if (NULL == node) return false;

	if (NULL == mHead) {
		// just add it to the head
		node->setNextPtr(mHead);
		mHead = node;
		mLength++;
		return true;
	}
	else {
		// return the node that has a value not greater than this node
		SingLinkedListNodePtr pos = notGreater(node->getValue());

		if (NULL == pos) {
			// can't find a node that has a value not greater than this node
			// this will only happen if the mHead is greater than this node
			// so insert this node before mHead
			// just add it to the head
			node->setNextPtr(mHead);
			mHead = node;
			mLength++;
			return true;
		}
		else {
			// insert this node after pos
			SingLinkedListNodePtr temp = pos->getNextPtr();
			node->setNextPtr(temp);
			pos->setNextPtr(node);
			mLength++;
			return true;
		}
	}
}


bool SingLinkedList::remove(uint32_t pos)
{
	// list is empty
	if (NULL == mHead) return false;

	if (0 == pos) {
		// just remove the head
		SingLinkedListNodePtr node = mHead->getNextPtr();
		delete mHead;
		mHead = node;
		mLength--;
		return true;
	}
	else {
		SingLinkedListNodePtr currentNode = mHead;
		SingLinkedListNodePtr nextNode = NULL;
		// move to the node just before the pos
		for (uint32_t count = pos - 1; count > 0 && currentNode != NULL; count--) {
			nextNode = currentNode->getNextPtr();
			currentNode = nextNode;
		}

		if (currentNode != NULL) {
			// next node is the node to be deleted
			nextNode = currentNode->getNextPtr();
	
			if (nextNode != NULL) {
				// just replace the next ptr
				currentNode->setNextPtr(nextNode->getNextPtr());

				delete nextNode;
		
				mLength--;

				return true;
			}
		}
	}

	return false;
}

		
void SingLinkedList::reverse() 
{
	if (mLength <= 1) return;

	SingLinkedListNodePtr previousNode = NULL;
	SingLinkedListNodePtr currentNode = mHead;

	// loop until end of list
	while (currentNode != NULL) {
		
		// get the next node
		SingLinkedListNodePtr nextNode = currentNode->getNextPtr();

		// set previous node as current next node
		currentNode->setNextPtr(previousNode);

		// move previous to current
		previousNode = currentNode;


		// move current to next
		currentNode = nextNode;
	}

	mHead = previousNode;

	return;
}

void SingLinkedList::reverse(SingLinkedListNodePtr previousNode, SingLinkedListNodePtr currentNode) 
{
	if (currentNode->getNextPtr() == NULL) {
		// at the end of the list
		mHead = currentNode;
	}
	else {
		// reverse the nextNode of the current node
		SingLinkedListNodePtr nextNode = currentNode->getNextPtr();
		
		reverse(currentNode, nextNode);
	}

	// previous node becomes next node
	currentNode->setNextPtr(previousNode);
}


bool SingLinkedList::present(uint32_t value) 
{
	// call the find api
	return (NULL != find(value));
}


SingLinkedListNodePtr SingLinkedList::find(uint32_t value) 
{
	if (mLength == 0) return false;

	SingLinkedListNodePtr currentNode = mHead;
	SingLinkedListNodePtr nextNode = NULL;
	// move to the node at the end
	while (currentNode->getNextPtr() != NULL) {
		nextNode = currentNode->getNextPtr();
		currentNode = nextNode;
	}	
	
	return find(value, mHead,  currentNode, mLength-1);
}


SingLinkedListNodePtr SingLinkedList::middle() const
{
	if (mLength == 0) return NULL;

	SingLinkedListNodePtr doubleStep = mHead;
	SingLinkedListNodePtr singleStep = mHead;
	// move doubleStep 2 nodes at a time
	// move singleStep 1 nodes at a time
	// when doubleStep is at the end, singleStep will give the node in the middle
	while (doubleStep != NULL) {
		doubleStep = doubleStep->getNextPtr();

		if (doubleStep != NULL) doubleStep = doubleStep->getNextPtr();

		// move singleStep only if doubleStep can move more than 2 steps
		if (doubleStep != NULL) singleStep = singleStep->getNextPtr();
	}	
	
	return singleStep;
}


SingLinkedListNodePtr SingLinkedList::last(uint32_t nth) const 
{
	if (mLength == 0) return NULL;

	SingLinkedListNodePtr currentNode = mHead;
	SingLinkedListNodePtr trailingNode = mHead;
	
	// move currentNode by nth node ahead of trailingNode
	for (uint32_t trail = 0; trail <= nth && currentNode != NULL; trail++) 
		currentNode = currentNode->getNextPtr();

	// then move both nodes together if not already at end of list
	while (currentNode != NULL) {
		trailingNode = trailingNode->getNextPtr();
		currentNode = currentNode->getNextPtr();
	}	
	
	return trailingNode;
}


SingLinkedListNodePtr SingLinkedList::find(uint32_t value, SingLinkedListNodePtr start, SingLinkedListNodePtr end, uint32_t distance) 
{
	cout << "find " << distance << " start " << start->getValue() << " end " << end->getValue() << endl;

	if (distance == 0) {
		// there is only 1 node
		if (start != NULL) {
			if (start->getValue() == value) return start;
		}

		return NULL;
	}
	else if (distance == 1) {
		// there are 2 nodes, this will return the last in the subset with the same value
		if (end != NULL) {
			if (end->getValue() == value) return end;
		}

		if (start != NULL) {
			if (start->getValue() == value) return start;
		}

		return NULL;
	}

	// & is a must to pass function as a function pointer argument
   // a member function must be qualified with the class name
	return foreachhalf(value, start,  end, distance, &SingLinkedList::find);
}


SingLinkedListNodePtr SingLinkedList::notGreater(uint32_t value)
{
	if (0 == mLength) return NULL;

	SingLinkedListNodePtr currentNode = mHead;
	SingLinkedListNodePtr nextNode = NULL;
	// move to the node at the end
	while (currentNode->getNextPtr() != NULL) {
		nextNode = currentNode->getNextPtr();
		currentNode = nextNode;
	}	
	
	return notGreater(value, mHead, currentNode, mLength-1);
}


SingLinkedListNodePtr SingLinkedList::notGreater(uint32_t value, SingLinkedListNodePtr start, SingLinkedListNodePtr end, uint32_t distance) 
{
	cout << "notGreater " << distance << " start " << start->getValue() << " end " << end->getValue() << endl;

	if (distance == 0) {
		// there is only 1 node
		if (start != NULL) {
			if (start->getValue() <= value) return start;
		}

		return NULL;
	}
	else if (distance == 1) {
		// there are 2 nodes
		if (end != NULL) {
			if (end->getValue() <= value) return end;
		}

		if (start != NULL) {
			if (start->getValue() <= value) return start;
		}

		return NULL;
	}

	// & is a must to poass function as a function pointer argument
   // a member function must be qualified with the class name
	return foreachhalf(value, start,  end, distance, &SingLinkedList::notGreater);
}


SingLinkedListNodePtr SingLinkedList::less(uint32_t value)
{
	if (0 == mLength) return NULL;

	SingLinkedListNodePtr currentNode = mHead;
	SingLinkedListNodePtr nextNode = NULL;
	// move to the node at the end
	while (currentNode->getNextPtr() != NULL) {
		nextNode = currentNode->getNextPtr();
		currentNode = nextNode;
	}	
	
	return less(value, mHead,  currentNode, mLength-1);
}


SingLinkedListNodePtr SingLinkedList::less(uint32_t value, SingLinkedListNodePtr start, SingLinkedListNodePtr end, uint32_t distance) 
{
	cout << "less " << distance << " start " << start->getValue() << " end " << end->getValue() << endl;

	if (distance == 0) {
		// there is only 1 node
		if (start != NULL) {
			if (start->getValue() < value) return start;
		}

		return NULL;
	}
	else if (distance == 1) {
		// there are 2 nodes
		if (end != NULL) {
			if (end->getValue() < value) return end;
		}

		if (start != NULL) {
			if (start->getValue() < value) return start;
		}

		return NULL;
	}

	// & is a must to poass function as a function pointer argument
   // a member function must be qualified with the class name
	return foreachhalf(value, start,  end, distance, &SingLinkedList::less);
}


SingLinkedListNodePtr SingLinkedList::foreachhalf(uint32_t value, SingLinkedListNodePtr start, SingLinkedListNodePtr end, uint32_t distance, SingLinkedListNodePtr(SingLinkedList::*func)(uint32_t, SingLinkedListNodePtr, SingLinkedListNodePtr, uint32_t))
{
	// if more than 2 nodes in the list
	// right shift 1 is same as divide by 2, but faster
	uint32_t pos = distance >> 1;

	SingLinkedListNodePtr currentNode = start;
	SingLinkedListNodePtr nextNode = NULL;
	// move to the node at pos
	for (uint32_t count = pos; count > 0 && currentNode != NULL; count--) {
		nextNode = currentNode->getNextPtr();
		currentNode = nextNode;
	}

	if (currentNode != NULL) {

		if (currentNode->getValue() >= value) {
			// search the 1st half
			return (this->*func)(value, start, currentNode, pos);
		}
		else {
			// if current node value <= value, search the 2nd half
			return (this->*func)(value, currentNode, end, distance-pos);
		}
	}	// if (currentNode != NULL) {

	return NULL;
}

ostream& SingLinkedList::traverse(ostream& out, const SingLinkedListNode& node) const
{
	// append value of the input node to the output stream
	out << node;

	// print out less than nodes
	if (NULL != node.getNextPtr()) {
		traverse(out, *node.getNextPtr());
	}

	return out;
}

ostream& operator<<(ostream& out, const SingLinkedList& tree)
{
	// is tree empty?
	if (NULL == tree.mHead) {
		return (out << "empty");
	}
	else {
		// traverse down the root to print out values of nodes
		return tree.traverse(out, *(tree.mHead));
	}
}


