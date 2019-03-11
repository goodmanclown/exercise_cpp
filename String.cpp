#include "String.hxx"

#include <algorithm>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


bool String::equalAlmost(const String& rhs) const
{
	if (this == &rhs) return false;

    if (mLen > rhs.mLen+1 || rhs.mLen > mLen+1) return false;

    uint32_t uDifferCount = 0;

	uint32_t myIndex = 0;
	uint32_t rhsIndex = 0; 
	while (myIndex < mLen && rhsIndex < rhs.mLen) {
		// match against the characters at the 2 index
		if (mStr[myIndex] == rhs.mStr[rhsIndex]) {
            // advance both pointers
            ++myIndex;
            ++rhsIndex;
		}
		else {
			++uDifferCount;

			if (uDifferCount > 1) {
				return false;
			}
			else if (mLen > rhs.mLen) {
				// mine is longer, advance my index
				++myIndex;
			} 
			else if (mLen < rhs.mLen) {
				// rhs is longer, advance rhs index
				++rhsIndex;
			}
			else {
				// advance both
				++myIndex;
				++rhsIndex;
			}
		}
	}

	if (mLen < rhs.mLen && myIndex == mLen) {
		uDifferCount = 1;
	}
	else if (mLen > rhs.mLen && rhsIndex == rhs.mLen) {
		uDifferCount = 1;
	}

    return (uDifferCount == 1);
}


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
	else if (len == 2) {

		// make a copy of the input
		char tmpWord[3];
		tmpWord[0] = word[0];
		tmpWord[1] = word[1];
		tmpWord[2] = 0;

        output.emplace_back(word);

		// swap the 2 characters to make the combination
		char temp = tmpWord[0];
		tmpWord[0] = tmpWord[1];
		tmpWord[1] = temp;
		output.emplace_back(tmpWord);

		return 2;
	} 


	for (uint32_t index=0; index < len; index++) {

        // make a copy of the input
        string tmpWord = string(&word[1], len-1);

		// remember the first char
		char temp = word[0];
		if (index > 0) {
			// swap first char with the char at the index
			temp = tmpWord[index-1];
			tmpWord[index-1] = word[0];
		}

		// call this api again with the new string
		vector<string> output1;

		uint32_t ret = shuffle(&tmpWord[0], len-1, output1);

		if (ret > 0) {
			// make a combination using the 1st character with output1 
			for (uint32_t j=0; j < ret; j++) {
				string str;
                str += temp;
				str += output1[j];
				output.push_back(str);
			}
		}
	} 

	return output.size();
}

void String::shuffleAndPrint()
{
	if (mLen == 0) return;

    string output;

	shuffleAndPrint(output, mStr);
		
	return;
}


void String::shuffleAndPrint(const string& prefix, char inputStr[])
{
    uint32_t inputStrLen = strlen(inputStr);

	if (inputStrLen == 0) 
    {
        cout << prefix <<  endl;

        return;
    }
	
    if (inputStrLen == 1)
    {
        cout << prefix << inputStr <<  endl;

        return;
    }

	if (inputStrLen == 2) 
    {
		// swap the 2 characters to make the combination
		char temp = inputStr[0];
		inputStr[0] = inputStr[1];
		inputStr[1] = temp;

        cout << prefix << inputStr <<  endl;

        // restore the input
		temp = inputStr[0];
		inputStr[0] = inputStr[1];
		inputStr[1] = temp;

        cout << prefix << inputStr <<  endl;

        return;
	} 

	for (uint32_t index=0; index < inputStrLen; ++index) 
    {
		// remember the first char
		char temp = inputStr[0];
		if (index > 0) {
			// swap first char with the char at the index
			temp = inputStr[index];
			inputStr[index] = inputStr[0];
			inputStr[0] = temp;
		}

		shuffleAndPrint(prefix + inputStr[0], &inputStr[1]);

		if (index > 0) {
			// restore the first char with the char at the index
			temp = inputStr[index];
			inputStr[index] = inputStr[0];
			inputStr[0] = temp;
		}
	} 

    return;
}

void String::reverse() 
{
	// if this object is empty or has only 1 character
	// just return, nothing to reverse
	if (mLen <= 1) return;

	// at most we need to loop until the middle of the string
	uint32_t strIndexMax = mLen / 2;
	int strIndexReverse = mLen-1;

	for (uint32_t strIndex=0; strIndex < strIndexMax; strIndex++, strIndexReverse--) {
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


uint32_t String::countWord(const char str[]) 
{
	uint32_t wordCount = 0;

	uint32_t len = strlen(str);

	// if input is empty, return 0
	if (len == 0) return wordCount;

    // scan the input from left to right
	for (uint32_t beginIndex=0; beginIndex < len-1; beginIndex++) {
        // kept the 1st char in a string
		string word;

        word += str[beginIndex];

	    for (uint32_t endIndex=beginIndex+1; endIndex < len; endIndex++) {
            // append the next char to the string
            word += str[endIndex];

            if (isWord(word.c_str(), word.length()) == true) wordCount++;
		}
	}

    // scan the input from right to left
	for (int beginIndex=len; beginIndex >= 1; beginIndex--) {
        // kept the 1st char in a string
		string word;

        word += str[beginIndex];

	    for (int endIndex=beginIndex-1; endIndex >= 0; endIndex--) {
            // append the next char to the string
            word += str[endIndex];

            if (isWord(word.c_str(), word.length()) == true) wordCount++;
		}
	}

	return wordCount;
}


uint32_t String::makeWord(vector<string>& output)
{
	uint32_t wordCount = 0;

	// if internal empty, return 0
	if (mLen == 0) return wordCount;

	// count the alphabets (case-insensitive) in this string
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

	for (uint32_t index = 0; index < 26; ++index) {
		string word;
		word += mStr[index];
		if (isWord(word.c_str(), word.length()) == true) {
			output.push_back(word);
		}
	}

	// count the number of char
	return wordCount;
}


bool String::isAllUnique()
{
    if (mLen == 0) return false;

    // each bit of these 2 integers represents the state of a character

    // 1 - character present
    // 0 - character not present 
    uint32_t uniqueBitArrayPresent = 0x0;

    // 1 - character present and not unique
    // 0 - character not present or unique
    uint32_t uniqueBitArrayNotUnique = 0x0;


    // loop through each character in this string
    for (uint32_t strIndex = 0; strIndex < mLen; ++strIndex)
    {
        uint8_t shiftValue = mStr[strIndex] - 'a';
        
        // first check if the character is already present
        if ( (uniqueBitArrayPresent & (1 << shiftValue)) > 0 )
        {   // this character already present
            // remember it
            uniqueBitArrayNotUnique |= (1 << shiftValue);
        }
        else
        {   // remember this character is present
            uniqueBitArrayPresent |= (1 << shiftValue);
        }
    }

    // return true if the Not Unique bit array is empty
	return (uniqueBitArrayNotUnique == 0);
}


void String::removeDuplicate()
{
    if (mLen == 0) return;

    bool bDone = false;

    uint32_t strIndexStart = 0;
    uint32_t strIndex = strIndexStart + 1;

    while (bDone == false)
    { 
        // assume no duplicate
        bDone = true;

        for (; strIndex < mLen; ++strIndex)
        {   // loop through each character and compare with the starting one

            if ( mStr[strIndexStart] == mStr[strIndex] )
            {   // replace this with the last character, if it's also not the same

                uint32_t strIndexLast = mLen - 1; 
                for (; strIndexLast > strIndex; --strIndexLast)
                {
                    if ( mStr[strIndexStart] != mStr[strIndexLast] )
                    {   // not the same 
                        break;
                    }
                    else
                    {   // remove this char
                        mStr[strIndexLast] = 0;
                        --mLen;
                    }
                }

                // replace this with the last character, if it's also not the same
                mStr[strIndex] = mStr[strIndexLast];

                // remove this char
                mStr[strIndexLast] = 0;
                --mLen;

                // had at least 1 duplicate
                bDone = false;
            }
        } 

        // move the pointer
        ++strIndexStart;
        strIndex = strIndexStart + 1;
    }
}


void String::escapeSpace()
{
    if (mLen == 0) return;

    // count the number of space in the internal buffer
    size_t countOfSpace = 0;
    for (size_t index=0; index < mLen; ++index)
    {
        if (mStr[index] == ' ') 
        {
            ++countOfSpace;
        }
    }

    // now know the number of spaces, calculate the extra number of bytes needed to keep the character '2' and '0'
    size_t extraNumberOfBytes = countOfSpace * 2;

}


size_t String::countMaxBracketDepth()
{
    if (mLen == 0) return 0;

    // count the maximum depth of bracket in the internal buffer
    size_t numLefBracket = 0;
    size_t numRightBracket = 0;
    for (size_t index=0; index < mLen; ++index)
    {
        if (mStr[index] == '(') 
        {
            ++numLefBracket;
        }
        else if (mStr[index] == ')') 
        {
            ++numRightBracket;
        }
    }

    if (numLefBracket == 0 || numRightBracket == 0)
    {
        return 0;
    }
    else if (numLefBracket == numRightBracket)
    {
        return numLefBracket;
    }
    else if (numLefBracket < numRightBracket)
    {
        return numLefBracket;
    }
    else 
    {
        return numRightBracket;
    }
}


vector<string> String::getKMostNGram(size_t k, size_t n)
{ 
    vector<string> result;

    if (!mLen || !k || !n )
    {
        return result;
    }

    // break the sentences into words
    vector<string> vWord;
    stringstream ss(mStr);
    string tok;

    while (getline(ss, tok, ' '))
    {
        vWord.push_back(tok);
    }

    if (vWord.size() < n)
    {
        return result;
    }

    // combine the words into NGram and count them
    unordered_map<string, size_t> mNGramCount;
    for (size_t index = 0; index <= (vWord.size() - n); ++index)
    {
        string nGram = vWord[index];
        for (size_t index1 = index+1; index1 < (index + n); ++index1)
        {
            nGram += " ";
            nGram += vWord[index1];
        }

        ++(mNGramCount[nGram]);
    }

    // use a sorted map to sort the size of the NGram
    // and only keep at most k pairs
    result.resize(k);
    size_t aMaxSize[k] = {};

    for (auto& kvpNGramCount : mNGramCount)
    { 
        size_t tmpMaxIndex = k;
        for (size_t indexToResult = 0; indexToResult < k; ++indexToResult)
        {
            if (aMaxSize[indexToResult] < kvpNGramCount.second)
            {
                tmpMaxIndex = indexToResult;
            }
        }
        
        if (tmpMaxIndex < k)
        {
            result[tmpMaxIndex] = kvpNGramCount.first;
            aMaxSize[tmpMaxIndex] = kvpNGramCount.second;
        }
    }
    
    return result;
}