#include <stdint.h>

#include <string.h>
#include <vector>
#include <string>

using std::vector;
using std::string;



/**
 * class representing a string
 */ 

class String {

public:


	/**
	 * Constructor
	 *
	 * @param: str 
	 *
	 */
	String(const char str[]) { 
		mLen = strlen(str);

		mStr = new char[mLen+1];

		strncpy(mStr, str, mLen);

		mStr[mLen] = '\0';
	};


	/**
	 * Constructor
	 *
	 */
	String():mLen(0),mStr(NULL) { 
	};


	/**
	 * Constructor
	 *
	 * @param: str 
	 * @param: len 
	 *
	 */
	String(const char str[], uint32_t len) { 
		mLen = len;

		mStr = new char[mLen+1];

		strncpy(mStr, str, mLen);

		mStr[mLen] = '\0';
	};


	/**
	 * Constructor
	 *
	 * @param: rhs 
	 *
	 */
	String(const String& rhs) { 
		mLen = rhs.mLen;

		mStr = NULL;
		if (mLen) {
			mStr = new char[mLen+1];

			strncpy(mStr, rhs.mStr, mLen);

			mStr[mLen] = '\0';
		}
	};


	/**
	 * Destructor
	 */
	virtual ~String() { delete [] mStr; };


	/**
	 * assignment operator
	 *
	 * @param: rhs 
	 *
	 */
	String& operator=(const String& rhs) { 
		if (this == &rhs) return *this;

		mLen = rhs.mLen;

		mStr = NULL;
		if (mLen) {
			mStr = new char[mLen+1];

			strncpy(mStr, rhs.mStr, mLen);

			mStr[mLen] = '\0';
		}

		return *this;
	};


	/**
	 * equal operator
	 *
	 * @param: rhs 
	 * @return true if equal 
	 *
	 */
	bool operator==(const String& rhs) const { 
		if (this == &rhs) return true;

		if (mLen != rhs.mLen) return false;

		if (strncmp(mStr, rhs.mStr, mLen) != 0) return false;

		return true;
	};


	/**
	 * @return true if input str is a substring 
	 */
	bool find(const char str[]) const;


	/**
	 * @return index of 1st occurence of input str.  -1 otherwise
	 */
	int indexOf(const char str[]) const;


	/**
	 * @return index of last occurence of input str.  -1 otherwise
	 */
	int lastIndexOf(const char str[]) const;


	/**
	 * @return number of splitted string in output vector.  0 otherwise
	 */
	uint32_t split(const char delimit[], vector<String>& output) const;



	/**
	 * @return number of splitted string in output vector.  0 otherwise
	 */
	uint32_t split(char delimit, vector<String>& output) const;


	/**
	 * @return true if this string is splitted into multiple words 
	 */
	bool split(string& splitted) const;


	/**
	 * @return number of combination
	 */
	uint32_t shuffle(vector<string>& output) const;


	/**
	 * @return mStr
	 */
	const char* data() const { return mStr; };

private:
	

	/**
	 * @return true if this string is splitted into multiple words 
	 */
	bool split(const char word[], uint32_t len, string& splitted) const;



	/**
	 * @return number of combination
	 */
	uint32_t shuffle(char word[], uint32_t len, vector<string>& output) const;


	/**
	 * @return true if input is a word in the internal word list
    */
	bool isWord(const char word[], uint32_t len) const;


	/**
	 * length of string
	 */
	uint32_t	mLen;


	/**
	 * string
	 */
	char*		mStr; 
};


