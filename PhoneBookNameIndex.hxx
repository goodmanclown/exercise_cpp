/**
 * a class representing the name index of phone book
 */

#include "BinaryTree.hxx"

#include <string>

using std::string;

class PhoneBookEntry;


/**
 * this is a class representing the name index of phone book, implemented as a BinaryTree
 */
class PhoneBookNameIndex : public BinaryTree<string> {

public:

	/**
    * @param: name - a string 
    * @param: entry - a pointer to an PhoneBookEntry to be associated with the input name 
    */
	bool add(const char name[], PhoneBookEntry* entry);

   /**
	 * @param: name
    */
   bool remove(const char name[]);


private:


};


