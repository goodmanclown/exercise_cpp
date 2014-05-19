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
		// move mStrIndex match against 1st character of str
		while (mStrIndex >= 0 && mStr[mStrIndex] != str[0]) mStrIndex--;

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

uint32_t String::split(const char delimit[], vector<string>& output) const
{
	//if this object is emtpy
	if (0 == mLen) return 0;

	uint32_t len = strlen(delimit);

	// if input is empty
	if (0 == len) return 0;

	// clear the output
	output.clear();

	return 0;
}
