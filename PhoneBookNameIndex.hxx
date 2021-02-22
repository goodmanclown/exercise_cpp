#pragma once

/**
 * a class representing the name index of phone book
 */

#include "BinarySearchTree.hxx"
#include "PhoneBookEntry.hxx"
#include "PhoneBookNameIndexEntry.hxx"

#include <string>

using std::string;

class PhoneBookEntry;


/**
 * this is a class representing the name index of phone book, implemented as a BinaryTree
 */
class PhoneBookNameIndex : public BinarySearchTree<string> {

public:

	/**
    * @param: name - a string 
    * @param: entry - a pointer to an PhoneBookEntry to be associated with the input name 
    * 
    * @return true if name is found
    */
	bool add(const char name[], const PhoneBookEntryPtr entry);

	/**
    * @param: name - a string 
    * 
    * @return pointer to BinaryTreeNode
    */
    PhoneBookNameIndexEntryPtr find(const char name[]) const;


   /**
	* @param: name - entry to be removed
    * 
    * @return true if name is removed
    */
   bool remove(const char name[]);


   /**
	* @param: name - name of entry to be removed
	* @param: phone - phone nmber of entry to be removed
    * 
    * @return true if name is removed
    */
   bool remove(const char name[], uint32_t phone);


private:


};


