#include "FindMissingNumber.hxx"

#include <math.h>
#include <iostream>

using namespace std;

void* start_thread(void* arg)
{
	if (NULL == arg) return NULL;

	// cast the arg back to the object
	FindMissingNumber& find = *((FindMissingNumber*)arg);

	// find the unique characters
	find.count();

	return NULL;
}

int FindMissingNumber::process(const unsigned char numbers[], unsigned int len)
{
  	cout << "start" << endl;   

	// transfer the input number to a list
	list<unsigned int> numbersList(numbers, numbers+len);

	// remove duplicate elements to reduce the list size
	numbersList.unique();

	// sorted the list
	numbersList.sort();

	list<unsigned int>::iterator iter = numbersList.begin();

	unsigned int num = 0;
	for (; iter != numbersList.end(); ++iter) {
		if (!num) num = *iter;
		else if ((*iter - num) == 1) num = *iter;
		else break;
	}

	cout << "done" << endl; 

	return num+1;
}


int FindMissingNumber::processThread(const unsigned char numbers[], unsigned int len)
{
  	cout << "start" << endl;   

	// arbitary divide the input into 2 half and process it
	unsigned int index2ndHalf = len / 2; 
	unsigned int len2ndHalf = len - index2ndHalf;
	// 1st half, from index 0 - (index2ndHalf-1)
	FindMissingNumber find1(numbers, index2ndHalf);
	pthread_t tid1;
	pthread_create(&tid1, NULL, start_thread, &find1);

	// 2nd half, from index2ndHalf - (len2ndHalf-1))
	FindMissingNumber find2(&(numbers[index2ndHalf]), len2ndHalf);
	pthread_t tid2;
	pthread_create(&tid2, NULL, start_thread, &find2);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	cout << "done" << endl; 

	// get the result
	unsigned long result1 = find1.getMissingNumberSet().to_ulong();
	unsigned long result2 = find2.getMissingNumberSet().to_ulong();

	// and together to find all values missing 
	unsigned long result = result1 & result2;
	
	MissingNumberSet resultSet(result);
	if (resultSet.count() == 1) return log2(result)+1;
	else if (resultSet.count() < 1) return -1;
	return -2;
}

void FindMissingNumber::count()
{
	if (!mInputNumberListLength) return;

	// remove duplicate elements to reduce the list size
	mInputNumberList.unique();

	InputNumberList::iterator iter = mInputNumberList.begin();

	for (; iter != mInputNumberList.end(); ++iter) {
		// reset the bit if value is found
		// value is 1-10
		// index is 0-9
		mMissingNumberSet.reset(*iter-1);
	}
}
