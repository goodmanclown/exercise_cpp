#include "SplitString.hxx"

#include <iostream>

using namespace std;

bool SplitString::split(const string& word, string& splitted) 
{
	char* wordSet[] = { "apple", "wood" };

	int len = word.length();

	if (0 == len) return false;

	int index = 0;

	// skip all the preceding white space
	while (' ' == word[index]) ++index;

	// empty string
	if (index >= len) return false;

	for (int index2=0; index2 < 2; index2++) {
		// check if the word is a substring
		size_t offset = word.find(wordSet[index2]);

		if (offset != npos && offset == index) {
			splitted = wordSet[index2];

			if (splitted.length() < len) {
				splitted += ' ';

				splitted 
			}
		}
	}

	return false;
}


bool SplitString::isWord(const string& word)
{
	char* wordSet[] = { "apple", "wood" };

	for (int index=0; index < 2; index++) {
		if (wordSet[index] == word) return true;	
	}

	return false;
}
