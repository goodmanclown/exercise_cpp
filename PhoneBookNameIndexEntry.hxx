/**
 * class representing an entry in the name index of phone book
 * it is a subclass of BinaryTreeNode since it will be stored in a BinaryTree
 * each character of a name is stored as a value of the node
 * 
 * the node of the last character of the store will have a list of PhoneBookEntry of the name
 */ 

#include "BinaryTreeNode.hxx"

#include "PhoneBook.hxx"

#include <stdint.h>
#include <string.h>


class PhoneBookNameIndexEntry : public BinaryTreeNode {

public:


	/**
	 * Constructor
	 *
	 * @param: name - a character of the name
	 *
	 */
	PhoneBookNameIndexEntry(char name):BinaryTreeNode(name) { };


	/**
	 * Destructor
	 */
	virtual ~PhoneBookNameIndexEntry() { };


	/**
	 *
	 * @return a reference to mPhoneBook
	 */
	PhoneBook& getPhoneBook() { return mPhoneBook; };


protected:


private:

	/**
	 * a PhoneBook
	 */
	PhoneBook		mPhoneBook;

};


