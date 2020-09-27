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
	String():mLen(0),mStr(nullptr) { };


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
	 * Copy Constructor
	 *
	 * @param: rhs 
	 *
	 */
	String(const String& rhs) { 
		mLen = rhs.mLen;

		mStr = nullptr;
		if (mLen) {
			mStr = new char[mLen+1];

			strncpy(mStr, rhs.mStr, mLen);

			mStr[mLen] = '\0';
		}
	};


	/**
	 * Move Constructor
	 *
	 * @param: rhs 
	 *
	 */
	String(String&& rhs) { 
		mLen = rhs.mLen;

        // move the pointer member
		mStr = rhs.mStr;

		// nullify the pointer member
		rhs.mStr = nullptr;
	};


	/**
	 * Destructor
	 */
	virtual ~String() { delete [] mStr; };


	/**
	 * copy assignment operator
	 *
	 * @param: rhs 
	 *
	 */
	String& operator=(const String& rhs) { 
		if (this == &rhs) return *this;

		mLen = rhs.mLen;

		mStr = nullptr;
		if (mLen) {
			mStr = new char[mLen+1];

			strncpy(mStr, rhs.mStr, mLen);

			mStr[mLen] = '\0';
		}

		return *this;
	};


	/**
	 * move assignment operator
	 *
	 * @param: rhs 
	 *
	 */
	String& operator=(String&& rhs) { 
		if (this == &rhs) return *this;

		mLen = rhs.mLen;

        // move the pointer member 
		mStr = rhs.mStr;
		
		// nullify the pointer member
		rhs.mStr = nullptr;

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
	 * almost equal operator
     * - inserting one character anywhere in the word (including at the beginning and end)
     * - removing one character
     * - replacing exactly one character
	 *
	 * @param: rhs 
	 * @return true if almost equal 
	 *
	 */
	bool equalAlmost(const String& rhs) const;


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
	 * @return vector of splitted string.  empty if error
	 */
	vector<String> split(const char delimit[]) const;


	/**
	 * @return vector of splitted string.  empty if error
	 */
	vector<String> split(char delimit) const;


	/**
	 * @return true if this string is splitted into multiple words 
	 */
	bool split(string& splitted) const;


	/**
	 * @return number of combination
	 */
	uint32_t shuffle(vector<string>& output) const;


	/**
	 * print out all the anagrams of this string
	 */
	void shuffleAndPrint();


	/**
	 * @return mStr
	 */
	const char* data() const { return mStr; };


	/**
	 * reverse the content of this string
	 */
	void reverse();


	/**
	 * @return true if this string has enough characters (case-insensitive) to construct the input note
	 */
	bool isEnough(char note[]);


	/**
	 * @return number of word in the internal word list is found in this string, from left and from right
	 */
	uint32_t countWord(const char str[]);


	/**
	 * @return number of words that can be made up with the characters of this string
	 */
	uint32_t makeWord(vector<string>& output);


	/**
	 * @return true if this string has all unique characters
	 */
	bool isAllUnique();


	/**
	 *
	 */
	void removeDuplicate();


	/**
	 *
	 */
	void escapeSpace();


	/**
	 *
	 */
	size_t countMaxBracketDepth();


	/**
	 * get the k most n-grams
     *
     * e.g., input text “The cow jumps over the moon”.“The cow jumps over the moon”
     * n=2 5 2-grams
     * The cow, cow jumps, jumps over, over the, the moon
     * n=3 4 3-grams
     * The cow jumps, cow jumps over, jumps over the, over the moon
	 */
	std::vector<std::string> getKMostNGram(size_t k, size_t n) const;

	/**
	 * strong password checker
     *
     * 
     * password is considered strong if below conditions are all met:
     *
     * It has at least 6 characters and at most 20 characters.
     * It must contain at least one lowercase letter, at least one uppercase letter, and at least one digit.
     * It must NOT contain three repeating characters in a row ("...aaa..." is weak, but "...aa...a..." is strong, 
     * assuming other conditions are met).
     *
     * Write a function strongPasswordChecker(s), that takes a string s as input, and return the MINIMUM change 
     * required to make s a strong password. If s is already strong, return 0.
     *
     * Insertion, deletion or replace of any one character are all considered as one change
	 */
	size_t strongPasswordChecker() const;

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
	 * 
	 */
	void shuffleAndPrint(const string& prefix, char inputStr[]);


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


