#include "SelectionSort.hxx"

#include <iostream>

using namespace std;

void SelectionSort::sort(uint32_t list[], uint32_t listLen)
{
	// if number is less than 2, do nothing
	if (listLen < 2) return;

	if (listLen > 2) {
		// we only need to do this until only 2 elements left in the array and do a simple swap with the remaining 2 if needed
		for (uint32_t indexOuterLoop=0; indexOuterLoop < listLen-2; indexOuterLoop++) {
			uint32_t minValue = list[indexOuterLoop];
			uint32_t minValueIndex = indexOuterLoop;

			for (uint32_t indexInnerLoop=indexOuterLoop+1; indexInnerLoop < listLen; indexInnerLoop++) {
				// find the smallest element
		
				cout << "indexO " << indexOuterLoop << " indexI " << indexInnerLoop << endl;

				if (list[indexInnerLoop] < minValue) {
					minValue = list[indexInnerLoop];
					minValueIndex = indexInnerLoop;
				}
			}

			if (minValueIndex != indexOuterLoop) {
				// swap their positions in the array
				uint32_t temp = list[indexOuterLoop];
				list[indexOuterLoop] = minValue;
				list[minValueIndex] = temp;
			}
		}
	}

	// do a simple swap with the remaining 2 if needed
	if (list[listLen-2] > list[listLen-1]) {
		// swap their positions in the array
		uint32_t temp = list[listLen-1];
		list[listLen-1] = list[listLen-2];
		list[listLen-2] = temp;
	}
}

