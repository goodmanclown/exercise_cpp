#pragma once

/**
 * a class representing the phone book
 */

#include "PhoneBookEntry.hxx"

#include <ostream>
#include <list>


/**
 * this is a class representing a phone book, implemented as a forward_list
 */
class PhoneBook : public std::list<PhoneBookEntryPtr> {

public:

    PhoneBook() = default;

    ~PhoneBook() = default;

    PhoneBook(const PhoneBook& rhs) = delete;

    PhoneBook& operator=(const PhoneBook& rhs) = delete;

	/**
    * @param: name - a string 
	 * @param: phone - a 10 digit number (assume American phone number)
	 * @param: address - a string
    */
	bool add(const char name[], uint32_t phone, const char address[]);


	/**
    * @param: entry - a pointer to a PhoneBookEntry object
    */
	bool add(PhoneBookEntryPtr entry);


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
	friend std::ostream& operator<<(std::ostream& out, const PhoneBook& tree);


private:


};


