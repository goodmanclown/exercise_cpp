#include "PhoneBookNameIndex.hxx"

#include "PhoneBookEntry.hxx"
#include "PhoneBookNameIndexEntry.hxx"

using namespace std;

bool PhoneBookNameIndex::add(const char name[], PhoneBookEntry* entry)
{
	// look up the name in the tree
	string nameIndex = name;
	PhoneBookNameIndexEntry* node = dynamic_cast<PhoneBookNameIndexEntry*>(find(nameIndex));

	if (NULL == node) {
		// the full name is not in the tree
		bool ret = insert(nameIndex);
	
		if (true == ret) {
			// find the name again
			PhoneBookNameIndexEntry* node = dynamic_cast<PhoneBookNameIndexEntry*>(find(nameIndex));
			if (node) node->setPhoneBookEntry(entry);

			return true;
		}
	}

	return false;
}
	
bool PhoneBookNameIndex::remove(const char name[])
{
	return true;
}


