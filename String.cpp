#include "String.hxx"

#include <iostream>

using namespace std;


bool String::find(const char str[]) const
{
	// return true if indexOf the input is not -1
	return (indexOf(str) != -1);
}

int String::indexOf(const char str[]) const
{
	// if this object is empty string
	if (mLen == 0) return -1;

	uint32_t len = strlen(str);

	// if input is an emptry string
	if (len == 0) return -1;
	
	// if input is longer that this object
	if (mLen < len) return -1;

	uint32_t mStrIndexMax = mLen - len + 1;
	
	for (uint32_t mStrIndex=0; mStrIndex < mStrIndexMax; mStrIndex++) {
		// match against 1st character of str
		if (mStr[mStrIndex] == str[0]) {
			// compare the rest of str
			uint32_t strIndex=1;
			for (uint32_t mStrIndex2=mStrIndex+1; mStrIndex2 < mLen && strIndex < len && mStr[mStrIndex2] == str[strIndex]; mStrIndex2++, strIndex++) {
				/* nothing to do */
			}

			// if we reach here matching up to the last character of str, we have a match
			if (strIndex == len) return mStrIndex;
		}
	}

	return -1;
}

int String::lastIndexOf(const char str[]) const
{
	// if this object is empty string
	if (mLen == 0) return -1;

	uint32_t len = strlen(str);

	// if input is an emptry string
	if (len == 0) return -1;
	
	// if input is longer that this object
	if (mLen < len) return -1;

	uint32_t mStrIndexMax = mLen - len + 1;
	
	for (int mStrIndex=mStrIndexMax; mStrIndex >= 0; mStrIndex--) {
		// match against 1st character of input
		if (mStr[mStrIndex] == str[0]) {
			// compare the rest of str
			uint32_t strIndex=1;
			for (uint32_t mStrIndex2=mStrIndex+1; mStrIndex2 < mLen && strIndex < len && mStr[mStrIndex2] == str[strIndex]; mStrIndex2++, strIndex++) {
				/* nothing to do */
			}

			// if we reach here matching up to the last character of str, we have a match
			if (strIndex == len) return mStrIndex;
		}
	}

	return -1;
}

uint32_t String::split(const char delimit[], vector<String>& output) const
{
	//if this object is emtpy
	if (0 == mLen) return 0;

	uint32_t len = strlen(delimit);

	// if input is empty
	if (0 == len) return 0;
	
	// clear the output
	output.clear();

	uint32_t mStrIndexBegin = 0;
	uint32_t mStrIndex = 0;
	for (; mStrIndex < mLen; mStrIndex++) {

		// see if this character is in the list of delimiter
		bool done = false;
		for (uint32_t index=0; index < len && done != true; index++) {
			if (mStr[mStrIndex] == delimit[index]) {
				// found a delimiter

				uint32_t substrlen = mStrIndex - mStrIndexBegin;

				cout << " begin " << mStrIndexBegin << ", index " << mStrIndex << ", len " << substrlen << endl;

				// make sure we don't have consecutive delimiter
				if (substrlen > 0) {
					// copy the substring to the output
					output.push_back(String(&mStr[mStrIndexBegin], substrlen));
				}

				// move the beginning index to right after the last found delimiter
				mStrIndexBegin = mStrIndex+1;

				// break the for loop
				done = true;
			}
		}
	}

	// see if we have any remaining characters left 
	uint32_t substrlen = mStrIndex - mStrIndexBegin;

	cout << " begin " << mStrIndexBegin << ", index " << mStrIndex << ", len " << substrlen << endl;

	if (substrlen > 0) {
		// copy the substring to the output
		output.push_back(String(&mStr[mStrIndexBegin], substrlen));
	}

	return output.size();
}

uint32_t String::split(char delimit, vector<String>& output) const
{
	//if this object is emtpy
	if (0 == mLen) return 0;

	// clear the output
	output.clear();

	uint32_t mStrIndexBegin = 0;
	uint32_t mStrIndex = 0;
	for (; mStrIndex < mLen; mStrIndex++) {
		// move mStrIndex match against 1st character of delimit
		if (mStr[mStrIndex] == delimit) {

			// a delimiter is found
			uint32_t substrlen = mStrIndex - mStrIndexBegin;

			cout << " begin " << mStrIndexBegin << ", index " << mStrIndex << ", len " << substrlen << endl;

			if (substrlen > 0) {
				// copy the substring to the output
				output.push_back(String(&mStr[mStrIndexBegin], substrlen));
			}

			// move the beginning index to right after the delimiter
			mStrIndexBegin = mStrIndex+1;
		}
	}

	// see if we have any remaining characters left 
	uint32_t substrlen = mStrIndex - mStrIndexBegin;

	cout << " begin " << mStrIndexBegin << ", index " << mStrIndex << ", len " << substrlen << endl;

	if (substrlen > 0) {
		// copy the substring to the output
		output.push_back(String(&mStr[mStrIndexBegin], substrlen));
	}

	return output.size();
}

bool String::split(string& splitted) const
{ 
	// if this string is empty
	if (0 == mLen) return false;

	uint32_t index = 0;

	// skip all the preceding white space
	while (index < mLen && (' ' == mStr[index])) ++index;

	// white space only
	if (index >= mLen) return false;

	uint32_t len = mLen - index;

	// first check if the whole mStr is in the wordset
	if (isWord(&mStr[index], len) == true) {
		// if yes, add the word to the splitted
		splitted += string(&mStr[index], len);
		return true;
	}
	else {
		while (index < mLen) {

			// move index2 until a word is found
			uint32_t index2 = 1;

			len = mLen - index;
			while (index2 < len && false == isWord(&mStr[index], index2)) index2++;

			cout << " index2 " << index2  <<  ", index " << index << ", len " << len << endl;

			uint32_t splitted_len = splitted.length();
			if (index2 >= len) {
				// the remaining is not a word, just append it and return

				if (splitted_len > 0) splitted += ' ';
				splitted += string(&mStr[index], index2);

				// if the input has never been splitted
				if (0 == splitted_len) return false;
				else return true;
			}

			if (splitted_len > 0) splitted += ' ';
			splitted += string(&mStr[index], index2);

			// move index to after the end of the last word
			index += index2;

			// skip all the intermediate white space, if any
			while (index < mLen && (' ' == mStr[index])) ++index;
		}
	}

	return true;
}


bool String::isWord(const char word[], uint32_t len) const
{
	static const char* wordSet[] = { "apple", "wood" };

	if (len == 0) return false;

	for (int index=0; index < 2; index++) {
		if (strlen(wordSet[index]) == len && (strncasecmp(wordSet[index], word, len) == 0)) return true;	
	}

	return false;
}

uint32_t String::shuffle(vector<string>& output) const 
{
	if (mLen == 0) return 0;

	uint32_t ret = shuffle(mStr, mLen, output);
		
	return ret;
}


uint32_t String::shuffle(char word[], uint32_t len, vector<string>& output) const 
{
	if (len == 0) return 0;
	
	if (len == 1) {
		output.push_back(string(word, len));
		return 1;
	}

	if (len == 2) {

		// swap the 2 characters to make the combination
		char temp = word[0];
		word[0] = word[1];
		word[1] = temp;
		output.push_back(string(word, len));

		// swap again the 2 characters to make the combination, and restore the input
		temp = word[0];
		word[0] = word[1];
		word[1] = temp;
		output.push_back(string(word, len));

		return 2;
	} 

	for (uint32_t index=0; index < len; index++) {
		if (index > 0) {
			char temp = word[0];
			word[0] = word[index];
			word[index] = temp;
		}

		// call this api again with the new string
		vector<string> output1;
		output1.clear();
		uint32_t ret = shuffle(&word[1], len-1, output1);

		if (ret > 0) {
			// make a combination using the 1st character with output1 
			for (uint32_t j=0; j < ret; j++) {
				string str = string(word, 1);
				str += output1[j];
				output.push_back(str);
			}
		}

		// restore the input string
		if (index > 0) {
			char temp = word[0];
			word[0] = word[index];
			word[index] = temp;
		}
	} 

	return output.size();
}

void String::reverse() 
{
	// if this object is empty or has only 1 character
	// just return, nothing to reverse
	if (mLen <= 1) return;

	// at most we need to loop until the middle of the string
	uint32_t strIndexMax = mLen / 2;
	int strIndexReverse = mLen-1;

	for (int strIndex=0; strIndex < strIndexMax; strIndex++, strIndexReverse--) {
		// swap the characters at the 2 indices
		char temp = mStr[strIndexReverse];
		mStr[strIndexReverse] = mStr[strIndex];
		mStr[strIndex] = temp;	
	}
}


bool String::isEnough(char note[]) 
{
	// if this object is empty, just return 
	if (mLen == 0) return false;

	uint32_t len = strlen(note);
	if (len == 0 || len > mLen) return false;

	// count the alphabets (case-insensitive, excludes white space) in this string
	uint32_t count[26];

	for (uint32_t index=0; index < mLen; index++) {
		// loop through each character
		char indexChar = mStr[index];
		if (indexChar >= 'a' && indexChar <= 'z') {
			count[indexChar - 'a']++;
		}
		else if (indexChar >= 'A' && indexChar <= 'Z') {
			count[indexChar - 'A']++;
		}
	}

	// go through the note and decrement the count for each alphabet
	// if any alphbet hits a count of zero, this string don't have enough character to
	// construct this note
	for (uint32_t index=0; index < len; index++) {
		// loop through each character
		char indexChar = note[index];
		if (indexChar >= 'a' && indexChar <= 'z') {
			if (count[indexChar - 'a'] <= 0) return false;

			count[indexChar - 'a']--;
		}
		else if (indexChar >= 'A' && indexChar <= 'Z') {
			if (count[indexChar - 'A'] <= 0) return false;

			count[indexChar - 'A']--;
		}
	}

	return true;
}

