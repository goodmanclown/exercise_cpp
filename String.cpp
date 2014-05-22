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
		// move mStrIndex match against 1st character of str
		while (mStrIndex < mStrIndexMax && mStr[mStrIndex] != str[0]) mStrIndex++;

		if (mStrIndex < mStrIndexMax) {
			// haven't reached the max yet
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
		// move mStrIndex match against 1st character of delimit
		while (mStrIndex < mLen && mStr[mStrIndex] != str[0]) mStrIndex--;

		if (mStrIndex >= 0) {
			// haven't reached the max yet
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
	for (uint32_t mStrIndex=0; mStrIndex < mLen; mStrIndex++) {
		// move mStrIndex match against any character of delimit
		while (mStrIndex < mLen) {

			// see if this character is in the list of delimiter
			uint32_t index=0;
			for ( ; index < len && mStr[mStrIndex] != delimit[index]; index++) ;

			// if yes, found a delimiter so break
			if (index < len) break;
			else mStrIndex++;
		}

		if (mStrIndex <= mLen) {
			// either a delimiter is found or reach the end of the mStr
			uint32_t substrlen = mStrIndex - mStrIndexBegin;

			cout << " begin " << mStrIndexBegin << ", index " << mStrIndex << ", len " << substrlen << endl;

			if (substrlen > 0) {
				// copy the substring to the output
				output.push_back(String(&mStr[mStrIndexBegin], substrlen));
			}

			// move mStrIndex match against any character of delimit
			while (mStrIndex < mLen) {

				// see if this character is in the list of delimiter
				uint32_t index=0;
				for ( ; index < len && mStr[mStrIndex] != delimit[index]; index++) ;

				// if yes, found a delimiter, continue to skip
				if (index < len) mStrIndex++;
				else break;
			}

			if (mStrIndex < mLen) mStrIndexBegin = mStrIndex;
		}
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
	for (uint32_t mStrIndex=0; mStrIndex < mLen; mStrIndex++) {
		// move mStrIndex match against 1st character of delimit
		while (mStrIndex < mLen && mStr[mStrIndex] != delimit) mStrIndex++;

		if (mStrIndex <= mLen) {
			// either a delimiter is found or reach the end of the mStr
			uint32_t substrlen = mStrIndex - mStrIndexBegin;

			cout << " begin " << mStrIndexBegin << ", index " << mStrIndex << ", len " << substrlen << endl;

			if (substrlen > 0) {
				// copy the substring to the output
				output.push_back(String(&mStr[mStrIndexBegin], substrlen));

				// move the beginning index to right after the delimiter
				if (mStrIndex < mLen) mStrIndexBegin = mStrIndex+1;
			}
		}
	}

	return output.size();
}

bool String::split(string& splitted) const
{ 
	// if this string is empty
	if (0 == mLen) return false;

	uint32_t index = 0;

	// skip all the preceding white space
	while (' ' == mStr[index]) ++index;

	// white space only
	if (index >= mLen) return false;

	splitted = "";

	// call the recursive api to split based on word set
	return split(mStr, mLen, splitted);
}

bool String::split(const char word[], uint32_t len, string& splitted) const 
{
	// if this string is empty
	if (0 == len) return true;

	uint32_t index = 0;

	// skip all the preceding white space
	while (' ' == word[index]) ++index;

	// white space only
	if (index >= len) return true;

	// first check if the whole word is in the wordset
	if (isWord(word, len) == true) {
		// if yes, add the word to the splitted
		splitted += string(word, len);
		return true;
	}
	else {
		// move index2 until a word is found
		uint32_t index2=1;
		while (index2 < len && false == isWord(word, index2)) index2++;

		cout << " index2 " << index2  <<  ", word " << word << ", len " << len << endl;

		if (index2 < len) {
			splitted += string(word, index2);
			splitted += ' ';

			// call this api again to check the remaining of the input string
			if (false == split(&word[index2], len-index2, splitted)) {
				// just put the remaining in the output
				splitted += string(&word[index2], len-index2);
			}

			return true;
		}
	}

	return false;
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

	// make a copy of the internal string without spaces
	char* temp = new char[mLen+1];

	strncpy(temp, mStr, mLen);

	temp[mLen] = '\0';
	
	uint32_t ret = shuffle(temp, mLen, output);
		
	delete [] temp;

	return ret;
}


uint32_t String::shuffle(const char word[], uint32_t len, vector<string>& output) const 
{
	if (len == 0) return 0;
	
	if (len == 1) {
		output.push_back(string(word, len));
		return 1;
	}

	if (len == 2) {
		output.push_back(string(word, len));

		// swap the 2 characters to make the combination
		char* temp = new char[len+1];
		temp[0] = word[1];
		temp[1] = word[0];
		temp[len] = '\0';

		output.push_back(string(temp, len));

		delete [] temp;

		return 2;
	} 

	// make a copy of the input string
	char* temp = new char[len+1];
	
	for (uint32_t index = 0; index < len; index++) {

		// copy the input to a temp 
		strncpy(temp, word, len);
		temp[len] = '\0';

		if (index > 0) {
			// do this swap if not the 1st time in this loop
			// swap the 1st character with the character at index to form a new combination
			char tmp = temp[0];
			temp[0] = temp[index];
			temp[index] = tmp;
		}

		// call this api again with the substring
		vector<string> output1;
		output1.clear();
		uint32_t ret = shuffle(&temp[1], len-1, output1);

		if (ret > 0) {
			// make a combination using the 1st character with output1 
			for (uint32_t j=0; j < ret; j++) {
				string str = string(temp, 1);
				str += output1[j];
				output.push_back(str);
			}
		}
	} 

	delete [] temp;

	return output.size();
}


uint32_t String::shuffleBySwap(char word[], uint32_t len, vector<string>& output) const 
{
	if (len == 0) return 0;
	
	if (len == 1) {
		output.push_back(string(word, len));
		return 1;
	}

	for (uint32_t outerLoop = 0; outerLoop < len; outerLoop++) {

		for (uint32_t innerLoop = 0; innerLoop < len-1; innerLoop++) {
			// shuffle the characters by swapping without neighbor
			char temp = word[innerLoop];
			word[innerLoop] = word[innerLoop+1];
			word[innerLoop+1] = temp;

			// add the combination to the output vector
			output.push_back(string(word, len));		
		}
	} 

	return output.size();
}

