/**
 * class representing an entry in the phone book
 * it is a subclass of SingLinkedListNode since it will be stored in a singular linked list
 * the phone number is stored as mValue of the parent
 */ 

#include "SingLinkedListNode.hxx"

#include <stdint.h>
#include <string.h>


class PhoneBookEntry : public SingLinkedListNode {

public:


	/**
	 * Constructor
	 *
	 * @param: name - a string 
	 * @param: phone - a 10 digit number (assume American phone number)
	 * @param: address - a string
	 *
	 */
	PhoneBookEntry(const char name[], uint32_t phone, const char address[]):SingLinkedListNode(phone),mAddress(0),mName(0) { 
		uint32_t len = strlen(address);
		mAddress = new char[len+1];
		strncpy(mAddress, address, len);
		mAddress[len] = '\0';

		len = strlen(name);
		mName = new char[len+1];
		strncpy(mName, name, len);
		mName[len] = '\0';
	};


	/**
	 * Copy Constructor
	 *
	 * @param: rhs - a reference to PhoneBookEntry to be copied
	 *
	 */
	PhoneBookEntry(const PhoneBookEntry& rhs):SingLinkedListNode(rhs),mAddress(0),mName(0) { 
		uint32_t len = strlen(rhs.mAddress);
		mAddress = new char[len+1];
		strncpy(mAddress, rhs.mAddress, len);
		mAddress[len] = '\0';

		len = strlen(rhs.mName);
		mName = new char[len+1];
		strncpy(mName, rhs.mName, len);
		mName[len] = '\0';
	};


	/**
	 * Destructor
	 */
	virtual ~PhoneBookEntry() { delete [] mAddress; delete [] mName; };


	/**
	  * assign operator
	  *
	  * @param: rhs - value to copied from
	  *
	  */
	PhoneBookEntry& operator=(const PhoneBookEntry& rhs) { 
		if (this == &rhs) return *this; 

		SingLinkedListNode::operator=(rhs);

		uint32_t len = strlen(rhs.mAddress);
		mAddress = new char[len+1];
		strncpy(mAddress, rhs.mAddress, len);
		mAddress[len] = '\0';

		len = strlen(rhs.mName);
		mName = new char[len+1];
		strncpy(mName, rhs.mName, len);
		mName[len] = '\0';
	};


	/**
	 *
    * @param address - a reference to char* to get mAddress
	 *
	 * @return length of mAddress
	 */
	uint32_t getAddress(char*& address) const { 
		if (0 == mAddress) return 0;

		address = mAddress; 

		return strlen(mAddress); 
	}


	/**
    *
    * @param name - a reference to char* to get mName
	 *
	 * @return length of mName
	 */
	uint32_t getName(char*& name) const { 
		if (0 == mName) return 0;

		name = mName;

		return strlen(mName); 
	};


	/**
	 * @return mPhone
	 */
	uint32_t	getPhone() const { return getValue(); };


protected:

	/**
	 * @param: out - a reference to output stream to append to
    *
	 * @return ostream of the content of this object
    */
	virtual ostream& append(ostream&out) const { 
		out << mName << " ";

		SingLinkedListNode::append(out);

		out << mAddress << std::endl;

		return out;
	};

private:

	/**
	 * address
	 */
	char*	mAddress;


	/**
	 * name
	 */
	char*	mName;


};


