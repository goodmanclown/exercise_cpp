#include "String.hxx"


bool String::find(const char str[])
{
	if (mLen == 0) return false;

	uint32_t len = strlen(str);

	if (len == 0) return false;

	if (mLen < len) return false;

	for (uint32_t index=0; index < mLen; index++) {
		if (len == 1) {
			if (mStr[index] == str[0]) return true;
		}	
		else {
			// do we have enough character remaining to compare
			if (mLen - index >= len) {
				return match(index, str);
			}
		}
	}

	return false;
}

bool String::match(uint32_t index, const char str[])
{
	// since we know the last character is also matched
	uint32_t len = strlen(str);	

	if (len == 1) {
		// only 1 character left
		return (mStr[index] == str[0]);
	}
	else {
		return match(index+1, &str[1]);
	}
} 
