/**
 * from the input 9 numbers, values between of 1-10, find out which number is missing 
 */ 

#include <bitset>
#include <list>
#include <string.h>

using namespace std;

class FindMissingNumber
{
public:

	/**
    * Constructor
	 */
	FindMissingNumber():mInputNumberList(),mInputNumberListLength(0),mMissingNumberSet() {};

	
	/**
    * Constructor
    *
	 * @param: numbers - an array of numbers
    * @param: len - len of input array
	 */
	FindMissingNumber(const unsigned char numbers[], unsigned int len):mInputNumberList(),mInputNumberListLength(len),mMissingNumberSet() { 
		// make a copy of the input
		mInputNumberList.insert(mInputNumberList.begin(), numbers, numbers+len);
	
		// set all bits to true
		mMissingNumberSet.set();
	};

	
	/**
	 * Destructor
	 */
	virtual ~FindMissingNumber() {};


	/**
	 *
	 * @param: numbers - an array of numbers
    * @param: len - len of input array
	 *
	 * @return int of the missing number. -1 if not found
	 */
	static int process(const unsigned char numbers[], unsigned int len);


	/**
	 *
	 * @param: numbers - an array of numbers
    * @param: len - len of input array
	 *
	 * @return int of the missing number. -1 if not found, -2 if more than 1
	 */
	static int processThread(const unsigned char numbers[], unsigned int len);


	/**
	 *	find the present number(s)
	 */
	void count();


	// 10 bits for value 1-10
	typedef bitset<10>		MissingNumberSet;

	/**
	 *	@return a reference to mMissingNumberSet
	 */
	const MissingNumberSet& getMissingNumberSet() const { return mMissingNumberSet; };


private:


	/**
	 * a pointer of a copy of input numbers
	 */
	typedef list<unsigned char>		InputNumberList;
	InputNumberList		mInputNumberList;

	/**
	 * length of input number list
	 */
	unsigned int	mInputNumberListLength;

	/**
	 * a set to keep track of which number is present in the input
	 */
	MissingNumberSet		mMissingNumberSet;
	
};


void* start_thread(void* arg);

