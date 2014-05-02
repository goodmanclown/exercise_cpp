#include "PhoneBookNameIndex.hxx"

#include "PhoneBookEntry.hxx"
#include "PhoneBookNameIndexEntry.hxx"

using namespace std;

bool PhoneBookNameIndex::add(const char name[], PhoneBookEntry* entry)
{
	// look up each character in the tree
	uint32_t len = strlen(name);
	uint32_t index = 0;
	PhoneBookNameIndexEntry* node = dynamic_cast<PhoneBookNameIndexEntry*>(find(name[index++]));
	for (; index < len && NULL != node; index++) {
		node = dynamic_cast<PhoneBookNameIndexEntry*>(find(name[index]));
	}
	
	if (index == len) {
		// this name is already in the tree
		// add the entry to the last node
		if (NULL != node) {
			node->getPhoneBook().add(entry); 
			return true;
		}
	}
	else {
		// the full name is not in the tree
		// add the remaining character to the tree
		bool ret = true;
		PhoneBookNameIndexEntry* node = NULL;
		for (; index < len && ret == true; index++) {

			node = new (nothrow) PhoneBookNameIndexEntry(name[index]);
			if (NULL == node) return false;

			ret = insert(node);
		}
	
		if (true == ret) {
			// all the nodes have been inserted

			// add the entry to the last node
			if (NULL != node) {
				node->getPhoneBook().add(entry); 
				return true;
			}
		}
	}

	return false;
}
	
bool PhoneBookNameIndex::remove(const char name[])
{
	return true;
}


