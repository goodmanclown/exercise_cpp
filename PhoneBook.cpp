#include "PhoneBook.hxx"

#include "PhoneBookEntry.hxx"

using namespace std;

bool PhoneBook::add(const char name[], uint32_t phone, const char address[])
{
	// create a PhoneBookEntry with the input
	PhoneBookEntry* entry = new (nothrow) PhoneBookEntry(name, phone, address);

	return add(entry);
}
	

bool PhoneBook::add(PhoneBookEntry* entry)
{
	// is input valid
	if (0 == entry) return false;

	// insert this entry into the list
	insert(entry);

	return true;
}


bool PhoneBook::remove(uint32_t phone)
{
	// see if this phone is in the head
	if (mHead != NULL && mHead->getValue() == phone) {
		// we are at the head
		SingLinkedListNodePtr entry = mHead;

		SingLinkedListNodePtr next = entry->getNextPtr();

		// set next as head
		mHead = next;

		// delete the entry
		delete entry;
	
		mLength--;

		return true;
	}
	else {
		// if not
		SingLinkedListNodePtr entry = find(phone);
	
		// phone is found?
		if (NULL == entry) return false;

		// since phone number is unique, use less api to find the entry immediately before the entry
		// to be removed
		SingLinkedListNodePtr prior = less(phone);
	
		if (NULL != prior) {
			SingLinkedListNodePtr next = entry->getNextPtr();

			// set next to after prior
			prior->setNextPtr(next);

			// delete the entry
			delete entry;

			mLength--;

			return true;
		}
	}

	return false;
}


ostream& operator<<(ostream& out, const PhoneBook& tree)
{
	// is tree empty?
	if (NULL == tree.mHead) {
		return (out << "empty");
	}
	else {
		// traverse down the root to print out values of nodes
		return tree.traverse(out, *(tree.mHead));
	}
}
