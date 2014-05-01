/**
 * a class representing the name index of phone book
 */

#include "TrinaryTree.hxx"

class PhoneBookEntry;


/**
 * this is a class representing the name index of phone book, implemented as a TrinaryTree
 */
class PhoneBookNameIndex : public TrinaryTree {

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


