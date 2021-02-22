#pragma once


/**
 * class representing an entry in the phone book
 * the phone number is stored as mValue of the parent
 */ 

#include <stdint.h>

#include <algorithm>
#include <memory>
#include <string>
#include <ostream>
#include <vector>


class PhoneBookEntry {

public:


	/**
	 * Constructor
	 *
	 * @param: name - a string 
	 * @param: phone - a 10 digit number (assume American phone number)
	 * @param: address - a string
	 *
	 */
	PhoneBookEntry(const char name[], 
                uint32_t phone, 
                const char address[])
                :
                mAddress(address),mName(name) { 
        mPhone.push_back(phone);
	};


	/**
	 * Copy Constructor
	 *
	 * @param: rhs - a reference to PhoneBookEntry to be copied
	 *
	 */
	PhoneBookEntry(const PhoneBookEntry& rhs) = default;


	/**
	 * Destructor
	 */
	virtual ~PhoneBookEntry() = default;


	/**
	  * assign operator
	  *
	  * @param: rhs - value to copied from
	  *
	  */
	PhoneBookEntry& operator=(const PhoneBookEntry& rhs) = default;


	/**
	  * equal operator
	  *
	  * @param: rhs - value to compare with
	  *
	  */
	bool operator==(const PhoneBookEntry& rhs) {
        if (mName != rhs.mName) return false;

        if (mAddress != rhs.mAddress) return false;

        if (mPhone.size() != rhs.mPhone.size()) return false;

        const auto& ret = std::mismatch(mPhone.cbegin(), mPhone.cend(), rhs.mPhone.cbegin(),
            [] (const auto& first, const auto& second) 
            {
                return first == second;
            }
        );

        // no mismatch if first element points to end of mPhone
        return (ret.first == mPhone.cend());
    };

	/**
	 * @return reference to mAddress
	 */
	const std::string& getAddress() const { return mAddress; };


	/**
	 * @return refernece to mName
	 */
	const std::string& getName() const { return mName; };


	/**
	 * @return mPhone
	 */
	const std::vector<uint32_t>& getPhone() const { return mPhone; };


	/**
	 * @return mPhone
	 */
	void addPhone(uint32_t phone) { mPhone.push_back(phone); };


	/**
	 * @param: out - a reference to output stream to append to
    *
	 * @return ostream of the content of this object
    */
	virtual std::ostream& append(std::ostream& out) const { 
		out << mName << " ";

        for (const auto& entry : mPhone)
        {
		    out << entry << " ";
        }

		out << mAddress << std::endl;

		return out;
	};

private:

	/**
	 * address
	 */
	std::string	mAddress;


	/**
	 * name
	 */
	std::string	mName;


    /**
     * phone
     */
    std::vector<uint32_t> mPhone;

};

using PhoneBookEntryPtr = std::shared_ptr<PhoneBookEntry>;
