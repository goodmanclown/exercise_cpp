#include <stdint.h>

#include <string>

using std::string;

/**
 * class representing a split string
 */ 

class SplitString {

public:


	/**
	 * @return true if input str is a substring 
	 */
	bool split(const string& word, string& splitted);

private:
	
	bool isWord(const string& word);

};


