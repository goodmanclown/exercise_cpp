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

			bool cont = false;
			do {
				cont = false;
				// see if this character is in the list of delimiter
				uint32_t index=0;
				for ( ; index < len && mStr[mStrIndex] != delimit[index]; index++) ;

				// if yes, move mStrIndex to the next character check
				if (index < len) {
					cont = true;
					mStrIndex++;
				}
			} while (cont == true);

			mStrIndex++;
		}

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
			else {
				// move the beginning index to right after the delimiter
				if (mStrIndex < mLen) mStrIndexBegin = mStrIndex+1;
			}
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
