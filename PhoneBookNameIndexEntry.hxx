/**
 * class representing an entry in the name index of phone book
 * it is a subclass of BinaryTreeNode since it will be stored in a BinaryTree
 * each character of a name is stored as a value of the node
 * 
 * the node of the last character of the store will have a list of PhoneBookEntry of the name
 */ 

#include "BinaryTreeNode.hxx"

#include <string>

using std::string;

class PhoneBookEntry;

class PhoneBookNameIndexEntry : public BinaryTreeNode<string> {

public:


	/**
	 * Constructor
	 *
	 * @param: name - a character of the name
	 *
	 */
	PhoneBookNameIndexEntry(const string& name):BinaryTreeNode<string>(name) { };


	/**
	 * Destructor
	 */
	virtual ~PhoneBookNameIndexEntry() { };


	/**
	 *
	 * @return a pointer to mPhoneBookEntry
	 */
	PhoneBookEntry* getPhoneBookEntry() { return mPhoneBookEntry; };


	/**
	 *
	 * @param entry - a pointer to mPhoneBookEntry
	 */
	void setPhoneBookEntry(PhoneBookEntry* entry) { mPhoneBookEntry = entry; };


protected:


private:

	/**
	 * a PhoneBookEntry
	 */
	PhoneBookEntry*	mPhoneBookEntry;

};


