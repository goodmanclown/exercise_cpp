#include "SingLinkedListNode.hxx"

#include <iostream>

using std::ostream;

/**
 * class representing a single linked list
 */ 
class SingLinkedList
{
public:


	/**
    * Constructor
	 */
	SingLinkedList():mHead(NULL),mLength(0) { };

	
	/**
    * Copy Constructor
	 */
	SingLinkedList(SingLinkedList& rhs);

	
	/**
	 * Destructor
	 */
	virtual ~SingLinkedList();


	/**
    * assignment operator=
	 */
	SingLinkedList& operator=(SingLinkedList& rhs);

	
	/**
    * assignment operator==
    *
    * @return true if these 2 linked lists are the same 
	 */
	bool operator==(SingLinkedList& rhs);

	
	/**
	 *
	 * @return SingLinkedListNodePtr at the beginning of the list and remove it from the list
	 */
	SingLinkedListNodePtr pop_front();


	/**
	 * @return mLength
	 */
	uint32_t getLength() const { return mLength; };


	/**
	 *
	 * @param: value - to be inserted to the tree
	 * @param: pos - to be inserted 
    *
	 * @return true if insert ok
	 *
	 */
	bool insert(uint32_t value, uint32_t pos);


	/**
	 *
	 * @param: pos - to be removed 
    *
	 * @return true if remove ok
	 */
	bool remove(uint32_t pos);


	/**
	 *
	 * @return true if reverse ok
	 */
	void reverse();


	/**
	 *
	 * @return true if value is found
	 */
	bool present(uint32_t value);


	/**
	 *
	 * @return node if value is found
	 */
	SingLinkedListNodePtr find(uint32_t value);


	/**
	 *
	 * @return node at the middle of the list
	 */
	SingLinkedListNodePtr middle();


   /** 
    * append to output stream
    *   
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to SingLinkedList to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */  
	friend ostream& operator<<(ostream& out, const SingLinkedList& tree);


protected:


	/**
	 *
	 * @param: node - to be inserted to the list, while maintaining the list in ascending order of mValue
    *
	 * @return true if insert ok
	 *
	 */
	bool insert(SingLinkedListNodePtr node);


	/**
	 *
	 * @return SingLinkedListNodePtr whose mValue is less than value 
	 */
	SingLinkedListNodePtr less(uint32_t value);


	/**
	 *
	 * @return SingLinkedListNodePtr whose mValue is not greater than value 
	 */
	SingLinkedListNodePtr notGreater(uint32_t value);


   /** 
    * append to value of the input node to output stream and traverse down all linked nodes
    *   
    * @param: out - a reference to output stream to append to
    * @param: node - a reference to SingLinkedListNode to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e., out
    */  
   ostream& traverse(ostream& out, const SingLinkedListNode& node) const;


	/**
	 * ptr to a SingLinkedListNode object
	 */
	SingLinkedListNodePtr		mHead;

	
	/**
	 * length of this list
	 */
	uint32_t		mLength;
	

private:


	/**
	 *
	 */
	void reverse(SingLinkedListNodePtr previousNode, SingLinkedListNodePtr currentNode);


	/**
	 *
	 * @return SingLinkedListNodePtr if value is found between start and end pos
	 */
	SingLinkedListNodePtr find(uint32_t value, SingLinkedListNodePtr start, SingLinkedListNodePtr end, uint32_t distance);


	/**
	 *
	 * @return SingLinkedListNodePtr found between start and end pos whose mValue is < value
	 */
	SingLinkedListNodePtr less(uint32_t value, SingLinkedListNodePtr start, SingLinkedListNodePtr end, uint32_t distance);


	/**
	 *
	 * @return SingLinkedListNodePtr found between start and end pos whose mValue is <= value
	 */
	SingLinkedListNodePtr notGreater(uint32_t value, SingLinkedListNodePtr start, SingLinkedListNodePtr end, uint32_t distance);


	/**
	 * a generic divide and conquer api
    * function as an argument must be a pointer.
    * member function must be qualified with the class name and enclosed with ( )
    * 
	 */
	SingLinkedListNodePtr foreachhalf(uint32_t value, SingLinkedListNodePtr start, SingLinkedListNodePtr end, uint32_t distance, SingLinkedListNodePtr(SingLinkedList::*func)(uint32_t, SingLinkedListNodePtr, SingLinkedListNodePtr, uint32_t));


};


