#include <stdint.h>

#include <string.h>
#include <vector>

using std::vector;



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

		mStr = new char[mLen];

		strncpy(mStr, str, mLen);
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

		mStr = new char[mLen];

		strncpy(mStr, str, mLen);
	};


	/**
	 * Constructor
	 *
	 * @param: rhs 
	 *
	 */
	String(const String& rhs) { 
		mLen = rhs.mLen;

		mStr = new char[mLen];

		strncpy(mStr, rhs.mStr, mLen);
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

		mStr = new char[mLen];

		strncpy(mStr, rhs.mStr, mLen);

		return *this;
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
	uint32_t split(char delimit, vector<String>& output) const;


private:
	
	/**
	 * length of string
	 */
	uint32_t	mLen;


	/**
	 * string
	 */
	char*		mStr; 
};


