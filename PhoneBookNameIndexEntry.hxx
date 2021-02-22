#pragma once

/**
 * class representing an entry in the name index of phone book
 * it is a subclass of BinaryTreeNode since it will be stored in a BinaryTree
 * each character of a name is stored as a value of the node
 * 
 * the node of the last character of the store will have a list of PhoneBookEntry of the name
 */ 

#include "BinaryTreeNode.hxx"
#include "PhoneBook.hxx"

#include <algorithm>
#include <memory>
#include <string>

using std::string;

class PhoneBookNameIndexEntry : public BinaryTreeNode<string> {

public:


	/**
	 * Constructor
	 *
	 * @param: name - a character of the name
	 *
	 */
	PhoneBookNameIndexEntry(const char name[]):BinaryTreeNode<string>(name) {};


	/**
	 * Constructor
	 *
	 * @param: name - a character of the name
	 *
	 */
	PhoneBookNameIndexEntry(const string& name):BinaryTreeNode<string>(name) {};


	/**
	 * Destructor
	 */
    ~PhoneBookNameIndexEntry() = default;


	/**
	 * @return a pointer to mPhoneBook
	 */
	const PhoneBook& getPhoneBook() const { return mPhoneBook; };


	/**
	 *
	 * @param entry - a pointer to mPhoneBookEntry
     * @return true if added
	 */
	bool adPhoneBookEntry(PhoneBookEntryPtr entry) {
        return mPhoneBook.add(entry);
    };

    void removePhoneBook() {
        mPhoneBook.clear();
    };


    void remove(uint32_t phone) {
        mPhoneBook.remove(phone);
    };


protected:


private:

	/**
	 * a PhoneBookEntry
	 */
	PhoneBook   mPhoneBook;

};


using PhoneBookNameIndexEntryPtr = std::shared_ptr<PhoneBookNameIndexEntry>;

