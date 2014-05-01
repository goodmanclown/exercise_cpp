/**
 * from the input string, find out which character is unqiue
 */ 

#include <string>

using namespace std;

class FindUniqueCharacter
{
public:

	/**
    * Constructor
	 */
	FindUniqueCharacter():mResultOnce(0),mResultMoreThanOnce(0),mStreamString("") { };

	
	/**
    * Constructor
    *
	 * @param: stream - an stream of characters 
	 * @param: len - length of input
	 */
	FindUniqueCharacter(const char stream[], unsigned int len):mResultOnce(0),mResultMoreThanOnce(0),mStreamString(stream, len) { };

	
	/**
	 * Destructor
	 */
	virtual ~FindUniqueCharacter() {};


	/**
	 *
	 * @param: stream - an stream of characters 
	 * @param: len - length of input
	 *
	 * @return char of the unique character.  # if not found
	 */
	static char process(const char stream[], unsigned int len);


	/**
	 *
	 * @param: stream - an stream of characters 
	 * @param: len - length of input
	 *
	 * @return char of the unique character.  # if not found
	 */
	static char processThread(const char stream[], unsigned int len);

	/**
	 *
	 * a function to call the recursive function
	 *
	 */
	void count();


private:

	/**
	 *
	 * a recursive function 
	 * @param: stream - an stream of characters 
	 * @param: len - length of input
	 *
	 */
	void count(const char stream[], unsigned int len);


	/**
	 *
	 * @return char of the unique character.  # if not found
	 *
	 */
	char getResult();


	/**
    * true if bit corresponding to each character in 'a' - 'z' is counted 
    * once
    */
	unsigned int mResultOnce;


	/**
    * true if bit corresponding to each character in 'a' - 'z' is counted 
    * more than once
    */
	unsigned int mResultMoreThanOnce;

	
	/**
	 * a string storing the input characters
	 */
	string	mStreamString;
};

int start_thread(void* arg);

