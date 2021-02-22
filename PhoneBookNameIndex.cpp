#include "PhoneBookNameIndex.hxx"

#include "PhoneBookNameIndexEntry.hxx"

#include <string.h>
#include <iterator>

using namespace std;

bool PhoneBookNameIndex::add(const char name[], const PhoneBookEntryPtr entry)
{
    bool bDone = false;
    do
    {
        size_t index = 0;
        size_t nameLen = strlen(name);
        string sName;
        BinaryTreeNodePtr<string> pNode = nullptr;
        for (; index < nameLen; ++index)
        {
            sName += name[index];
            pNode = BinarySearchTree<string>::find(sName);
            if (pNode == nullptr) {
                break;
            }
        }

        if (index == nameLen) {
            // the entire name is found, jsut add the enry to the last node
            if (pNode != nullptr) {
                auto pIndexNode = dynamic_pointer_cast<PhoneBookNameIndexEntry>(pNode);
                if (pIndexNode != nullptr) {
                    return pIndexNode->adPhoneBookEntry(entry);
                }
            }
        }
        else {
            // insert the remaining characters into the BST
            PhoneBookNameIndexEntryPtr pIndexNode = make_shared<PhoneBookNameIndexEntry>(sName);
            BinarySearchTree<string>::insert(static_pointer_cast<BinaryTreeNode<string>>(pIndexNode));

            for (++index; index < nameLen; ++index)
            {
                sName += name[index];   
                // insert the remaining characters into the BST
                PhoneBookNameIndexEntryPtr pIndexNode = make_shared<PhoneBookNameIndexEntry>(sName);
                BinarySearchTree<string>::insert(static_pointer_cast<BinaryTreeNode<string>>(pIndexNode));
            }
        }
    } while (!bDone);
    
	return false;
}

bool PhoneBookNameIndex::remove(const char name[])
{
	// look up the name in the tree
	const auto node = find(name);

	if (nullptr != node) {
        node->removePhoneBook();
	}

	return false;
}

bool PhoneBookNameIndex::remove(const char name[], uint32_t phone)
{
	// look up the name in the tree
	auto node = find(name);

	if (nullptr != node) {
        node->remove(phone);
	}

	return false;
}

PhoneBookNameIndexEntryPtr PhoneBookNameIndex::find(const char name[]) const
{
    size_t index = 0;
    size_t nameLen = strlen(name);
    BinaryTreeNodePtr<string> pNode = nullptr;
    string sName;
    for (; index < nameLen; ++index)
    {
        sName += name[index];
        pNode = BinarySearchTree<string>::find(sName);
        if (pNode == nullptr) {
            break;
        }
    }

    if (index < nameLen) {
        return nullptr;
    }
    else {
        return dynamic_pointer_cast<PhoneBookNameIndexEntry>(pNode);
    }
}


