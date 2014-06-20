/**
 * template function to do bubble select in ascending order
 * the type of input array must implement operator< and operator==
 */ 

#include <stdint.h>
#include <iostream>

using std::cout;
using std::endl;

class SelectionSelect {

public:

	/**
	 * @param inputElem - an array of <T> to be sorted
	 * @param numOfInputElem - number of elements in the input array
	 * @param asc - true if sort in ascending order
	 * @param kth - number of max / min elements to be selected
	 */
	template <typename T>
	static void select(T inputElem[], uint32_t numOfInputElem, bool asc, uint32_t kth)
	{
		// if input is empty, do nothing
		if (!numOfInputElem) return;

		// if number is less than kth, do nothing
		if (numOfInputElem <= kth) return;

		// we only need to do this until kth
		for (uint32_t indexOuterLoop=0; indexOuterLoop <= kth; indexOuterLoop++) {
			T value = inputElem[indexOuterLoop];
			uint32_t valueIndex = indexOuterLoop;

			for (uint32_t indexInnerLoop=indexOuterLoop+1; indexInnerLoop < numOfInputElem; indexInnerLoop++) {
				cout << "indexO " << indexOuterLoop << " indexI " << indexInnerLoop << endl;

				if (asc == true) {
					if (inputElem[indexInnerLoop] < value) {
						value = inputElem[indexInnerLoop];
						valueIndex = indexInnerLoop;
					}
				}
				else {
					if (inputElem[indexInnerLoop] > value) {
						value = inputElem[indexInnerLoop];
						valueIndex = indexInnerLoop;
					}
				}
			}

			if (valueIndex != indexOuterLoop) {
				// swap their positions in the array
				uint32_t temp = inputElem[indexOuterLoop];
				inputElem[indexOuterLoop] = value;
				inputElem[valueIndex] = temp;
			}
		} 	// for (uint32_t indexOuterLoop=0; indexOuterLoop <= kth; indexOuterLoop++) {
	}
};


