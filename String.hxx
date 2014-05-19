#include <stdint.h>

#include <string.h>
#include <vector>
#include <string>

using std::string;
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
	 * Destructor
	 */
	virtual ~String() { delete [] mStr; };


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
	uint32_t split(const char delimit[], vector<string>& output) const;


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


