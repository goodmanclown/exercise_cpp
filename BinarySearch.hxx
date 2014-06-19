/**
 * template function to do binary search in a sorted array
 * the type of input array must implement operator< and operator==
 */ 

#include <stdint.h>
#include <iostream>

using std::cout;
using std::endl;

class BinarySearch {

public:

	/**
	 * @param inputElem - an array of <T> to be searched
	 * @param numOfInputElem - number of elements in the input array
	 * @param value - value to be searched in the array
    *
	 * @return true if value is found in the array
	 */
	template <typename T>
	static int search(T inputElem[], uint32_t startIndex, uint32_t endIndex, T value)
	{
		cout << " start " << startIndex << " end " << endIndex << endl;

		// if input is empty, do nothing
		uint32_t numOfInputElem = endIndex + 1 - startIndex;
		if (0 >= numOfInputElem) return -1;

		// if input has only 1 element, just compare and return the comparison result
		if (1 == numOfInputElem) {
			if (inputElem[startIndex] == value) return startIndex;
			else return -1;
		}

		if (2 == numOfInputElem) {
			if (inputElem[endIndex] == value) return endIndex;
			else if (inputElem[startIndex] == value) return startIndex;
			else return -1;
		}

		// found the index to the middle of the input array
		uint32_t indexToHalf = numOfInputElem / 2;

		if (value < inputElem[startIndex+indexToHalf]) {
			// search the value in the 1st half of the array
			cout << " search 1st half" << endl;
			return search(inputElem, startIndex, startIndex+indexToHalf-1, value);
		}
		else {
			// search the value in the 2nd half of the array
			cout << " search 2nd half" << endl;
			return search(inputElem, startIndex+indexToHalf, endIndex, value);
		}
	}
};


