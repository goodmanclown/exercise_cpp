#include "FindUniqueCharacter.hxx"

#include <iostream>
#include <math.h>
#include <pthread.h>

int start_thread(void* arg)
{
	if (NULL == arg) return -1;

	// cast the arg back to the object
	FindUniqueCharacter find = *((FindUniqueCharacter*)arg);

	// find the unique characters
	find.count();

	return 0;
}

char FindUniqueCharacter::process(const char stream[], unsigned int len)
{
  	cout << "start" << endl;   

	FindUniqueCharacter find;
	find.count(stream, len);

	cout << "done" << endl; 

	return find.getResult();
}


char FindUniqueCharacter::processThread(const char stream[], unsigned int len)
{
  	cout << "start" << endl;   

	// arbitary divide the input into 2 half and process it
	unsigned int index2ndHalf = len / 2; 
	unsigned int len2ndHalf = len - index2ndHalf;
	// 1st half, from index 0 - (index2ndHalf-1)
	FindUniqueCharacter find1(stream, index2ndHalf);

	// 2nd half, from index2ndHalf - (len2ndHalf-1))
	FindUniqueCharacter find2(&(stream[index2ndHalf]), len2ndHalf);
	
	cout << "done" << endl; 

	return find1.getResult();
}


void FindUniqueCharacter::count()
{
	count(mStreamString.c_str(), mStreamString.size());
}


char FindUniqueCharacter::getResult()
{
	if (mResultOnce) {
		double result = log2((double)mResultOnce);
		return (char)result + 'a';
	}
	else {
		// no character has appeared only once
		return '#';
	}
}

void FindUniqueCharacter::count(const char stream[], unsigned int len)
{
	if (len == 1) {
		// only 1 char in the input, just calculate the frequency
		char schar = stream[0];
		char lowerCaseSchar = tolower(schar);
		// 'a' - 'z' are consecutive in values
		unsigned int indexCharacter = lowerCaseSchar - 'a';

		unsigned int once = mResultOnce & (1 << indexCharacter);
		unsigned int moreThanOnce = mResultMoreThanOnce & (1<<indexCharacter);

		if (0 == once && 0 == moreThanOnce) {
			// this char has not appeared before
			mResultOnce |= (1 << indexCharacter);
		}
		else if (0 < once && 0 == moreThanOnce) {
			// this char has already once
			mResultOnce &= ~(1 << indexCharacter);
			mResultMoreThanOnce |= (1 << indexCharacter);
		}
	}
	else {
		// arbitary divide the input into 2 half and process it
		unsigned int index2ndHalf = len / 2; 
		unsigned int len2ndHalf = len - index2ndHalf;
		// 1st half, from index 0 - (index2ndHalf-1)
		count(stream, index2ndHalf);

		// 2nd half, from index2ndHalf - (len2ndHalf-1))
		count(&(stream[index2ndHalf]), len2ndHalf);
	}
}
