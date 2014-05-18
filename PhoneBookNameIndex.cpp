#include "PhoneBookNameIndex.hxx"

#include "PhoneBookEntry.hxx"
#include "PhoneBookNameIndexEntry.hxx"

using namespace std;

bool PhoneBookNameIndex::add(const char name[], PhoneBookEntry* entry)
{
	// look up the name in the tree
	string nameIndex = name;
	BinaryTreeNode<string>* node = find(nameIndex);

	if (NULL == node) {
		// the full name is not in the tree
		PhoneBookNameIndexEntry* index = new PhoneBookNameIndexEntry(nameIndex);
		bool ret = insert(index);
	
		if (true == ret) {
			// find the name again
			PhoneBookNameIndexEntry* node = dynamic_cast<PhoneBookNameIndexEntry*>(find(nameIndex));
			if (node) {
				node->setPhoneBookEntry(entry);

				return true;
			}
		}
	}

	return false;
}
	
bool PhoneBookNameIndex::remove(const char name[])
{
	// look up the name in the tree
	string nameIndex = name;
	BinaryTreeNode<string>* node = find(nameIndex);

	if (NULL != node) {
		return BinaryTree<string>::remove(nameIndex);
	}

	return false;
}


