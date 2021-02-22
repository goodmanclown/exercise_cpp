#include "PhoneBook.hxx"

#include <algorithm>
#include <iostream>

using namespace std;

bool PhoneBook::add(const char name[], uint32_t phone, const char address[])
{
	// create a PhoneBookEntry with the input
	PhoneBookEntryPtr entry = make_shared<PhoneBookEntry>(name, phone, address);

	return add(entry);
}
	

bool PhoneBook::add(PhoneBookEntryPtr entry)
{
	// is input valid
	if (nullptr == entry) return false;

    // check if the entry is in this list
    auto iter = begin();
    for (; iter != end(); ++iter) {
        if (*(*iter) == *entry) {
            return false;
        }
    }

	// insert this entry into the list
	push_back(entry);

	return true;
}


bool PhoneBook::remove(uint32_t phone)
{
    // check if the phone number is in this list
    auto iter = begin();
    for (; iter != end(); ++iter) {
        const auto& vPhone = (*iter)->getPhone();
        bool ret = false;
        for (const auto& entry : vPhone) {
            if (entry == phone) {
                ret = true;
                break;
            }
        }

        if (ret == true) {
            break;
        }
    }

    if (iter == end()) return false;

    erase(iter);

	return true;
}


ostream& operator<<(ostream& out, const PhoneBook& tree)
{
	// is tree empty?
	if (tree.empty() == true) {
		return out << "empty";
	}
	else {
		// traverse down the root to print out values of nodes
        for_each(tree.cbegin(), tree.cend(), 
            [&out](const auto& entry)
            {
                entry->append(out);
            }
        );

        return out;
	}
}
