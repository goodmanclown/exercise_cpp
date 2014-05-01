#include "BubbleSort.hxx"

#include <iostream>

using namespace std;

void BubbleSort::sort(MdnEndpoint inputElem[], uInt numOfInputElem)
{
	// if number is 0, do nothing
	if (!numOfInputElem) return;

	// assume swap is required to start the first pass
	bool swapOccurred = true;
	uInt count = 0;
	for (uInt indexOuterLoop=0; indexOuterLoop < numOfInputElem-1 && swapOccurred == true; indexOuterLoop++) {
		// initialize to false  
		swapOccurred = false;
		for (uInt indexInnerLoop=0; indexInnerLoop < numOfInputElem-1; indexInnerLoop++) {
			// compare adjacent element				
		
			std::cout << "indexO " << indexOuterLoop << " indexI " << indexInnerLoop << endl;

			if (inputElem[indexInnerLoop+1] < inputElem[indexInnerLoop]) {
				// swap their positions in the array
				MdnEndpoint temp = inputElem[indexInnerLoop];
				inputElem[indexInnerLoop] = inputElem[indexInnerLoop+1];
				inputElem[indexInnerLoop+1] = temp;

				// indicates a swap has occurred
				swapOccurred = true;

				count++;
			}	
		}
	}

	std::cout << "count " << count << endl;

}

