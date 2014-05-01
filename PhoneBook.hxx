/**
 * a class representing the phone book
 */

#include "SingLinkedList.hxx"

#include <stdint.h>

class PhoneBookEntry;


/**
 * this is a class representing a phone book, implemented as a SingLinkedList
 */
class PhoneBook : public SingLinkedList {

public:

	/**
    * @param: name - a string 
	 * @param: phone - a 10 digit number (assume American phone number)
	 * @param: address - a string
    */
	bool add(const char name[], uint32_t phone, const char address[]);


	/**
    * @param: entry - a pointer to a PhoneBookEntry object
    */
	bool add(PhoneBookEntry* entry);


   /**
	 * @param: phone - a 10 digit number (assume American phone number)
    */
   bool remove(uint32_t phone);


   /** 
    * append to output stream
    *   
    * @param: out - a reference to output stream to append to
    * @param: tree - a reference to PhoneBook to append to
    *   
    * @return a reference to ostream appended with values of nodes of this tree, i.e, out
    */  
	friend ostream& operator<<(ostream& out, const PhoneBook& tree);


private:


};


