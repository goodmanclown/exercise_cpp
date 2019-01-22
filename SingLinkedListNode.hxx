#ifndef _SINGLINKEDLISTNODE_
#define _SINGLINKEDLISTNODE_

#include <stdint.h>
#include <iostream>

using std::ostream;

class SingLinkedListNode;

using SingLinkedListNodePtr=SingLinkedListNode*;


/**
 * class representing the node of a single linked list
 */ 
class SingLinkedListNode {

public:

	/**
	 * Constructor
	 *
	 * @param: value - value of this node
	 *
	 */
	explicit SingLinkedListNode(uint32_t value):mNextPtr(nullptr),mValue(value) { };


	/**
	 * Copy Constructor
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	SingLinkedListNode(const SingLinkedListNode& rhs):mNextPtr(rhs.mNextPtr),mValue(rhs.mValue) { };


	/**
	 * Destructor
	 */
	virtual ~SingLinkedListNode();


	/**
	 * assign operator
	 *
	 * @param: rhs - value to copied from
	 *
	 */
	SingLinkedListNode& operator=(const SingLinkedListNode& rhs);


	/**
	 * @return mValue
     */
	uint32_t getValue() const { return mValue; };


	/**
	 * @return mValue
     */
	void setValue(uint32_t value) { mValue = value; };


	/**
	 * @return mNextPtr
    */
	SingLinkedListNodePtr getNextPtr() const { return mNextPtr; };


	/**
	 * @param ptr - a pointer to a SingLinkedListNode object to be inserted between this node and next node
    */
	void insert(SingLinkedListNodePtr ptr);


	/**
	 * @param ptr - a pointer to a SingLinkedListNode object to be set to mNextToPtr
    */
	void setNextPtr(SingLinkedListNodePtr ptr) { mNextPtr = ptr; };


	/**
	 * append to output stream
	 *
	 * @param: out - a reference to output stream to append to
	 *
	 * @return a reference to ostream appended with value of this node, i.e, out
	 */
	friend ostream& operator<<(ostream& out, const SingLinkedListNode& node) { return node.append(out); };


protected:

	/**
	 * @param: out - a reference to output stream to append to
    *
	 * @return ostream of the content of this object
    */
	virtual ostream& append(ostream&out) const { out << mValue << " "; return out; };


private:

	/**
	 * pointer to next node 
	 */
	SingLinkedListNodePtr 	mNextPtr;


	/**
	 * value of this node
	 */
	uint32_t	mValue;

};


#endif // _SINGLINKEDLISTNODE_
