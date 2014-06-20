/**
 * template function to do bubble select in ascending order
 * the type of input array must implement operator< and operator==
 */ 

#include <stdint.h>

class BubbleSelect {

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

		// assume swap is required to start the first pass
		bool swapOccurred = true;
		for (uint32_t indexOuterLoop=0; indexOuterLoop <= kth && swapOccurred == true; indexOuterLoop++) {
			// initialize to false  
			swapOccurred = false;
			for (uint32_t indexInnerLoop=0; indexInnerLoop < numOfInputElem-1; indexInnerLoop++) {
				// compare adjacent element				
		
				bool swap = false;
				if (true == asc) {
					// ascending order
					if (inputElem[indexInnerLoop+1] < inputElem[indexInnerLoop]) swap = true;
				}
				else {
					// decending order
					if (inputElem[indexInnerLoop+1] > inputElem[indexInnerLoop]) swap = true;
				}

				if (true == swap) {
					// swap their positions in the array
					T temp = inputElem[indexInnerLoop];
					inputElem[indexInnerLoop] = inputElem[indexInnerLoop+1];
					inputElem[indexInnerLoop+1] = temp;
		
					// indicates a swap has occurred
					swapOccurred = true;
				}
			}
		}
	}
};


