#include "InsertionSort.hxx"

#include <iostream>

using namespace std;

void InsertionSort::sort(uint32_t list[], uint32_t listLen)
{
	// if number is less than 2, do nothing
	if (listLen < 1) return;

	// go through the unsorted list 1 element at a time
	for (uint32_t indexOuterLoop=1; indexOuterLoop < listLen; indexOuterLoop++) {

		// scan through the sorted list
		bool done = false;
		for (uint32_t indexInnerLoop=0; indexInnerLoop < indexOuterLoop && false == done; indexInnerLoop++) {
			// find the element, from the sorted list, that is greater than the current one
		
			cout << "indexO " << indexOuterLoop << " " << list[indexOuterLoop] << " indexI " << indexInnerLoop << " " << list[indexInnerLoop] << endl;

			if (list[indexInnerLoop] > list[indexOuterLoop]) {

				uint32_t temp = list[indexOuterLoop];

				// move the elements to make space for the lesser value
				for (int index=indexOuterLoop; index > indexInnerLoop; index--) {
					list[index] = list[index-1];
				}

				list[indexInnerLoop] = temp;
				
				// break the for inner loop
				done = true;
			}
		}	
	}
}

