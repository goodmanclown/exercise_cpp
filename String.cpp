#include "String.hxx"

#include <iostream>

using namespace std;

bool String::find(const char str[])
{
	// if this object is empty string
	if (mLen == 0) return false;

	uint32_t len = strlen(str);

	// if input is an emptry string
	if (len == 0) return false;
	
	// if input is longer that this object
	if (mLen < len) return false;

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
			if (strIndex == len) return true;
		}
	}

	return false;
}

