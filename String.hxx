#include <stdint.h>

#include <string.h>

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
	 * Destructor
	 */
	virtual ~String() { delete [] mStr; };


	/**
	 * @return true if input str is a substring 
	 */
	bool find(const char str[]);

private:
	
	/**
	 * length of string
	 */
	uint32_t	mLen;


	/**
	 * string
	 */
	char*		mStr; };


