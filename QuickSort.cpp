#include "QuickSort.hxx"

#include <iostream>

using namespace std;

bool QuickSort::sort(uint32_t list[], uint32_t listLen)
{
	for (int index=0; index < listLen; index++)
		cout << list[index] << " ";
	cout << endl;

	if (listLen <= 1) 
		return true;
	else if (listLen == 2) {
		// just a simple swap
		if (list[0] > list[1]) {
			uint32_t temp = list[0];
			list[1] = list[0];
			list[0] = temp;
		}
	}
	else {
		// pick the value in the middle of the list as pivot
		uint32_t pivotIndex = listLen/2;
		uint32_t pivot = list[pivotIndex];

		// swap the pivot with the elements at the end
		uint32_t temp = list[listLen - 1];
		list[listLen - 1] = pivot;
		list[pivotIndex] = temp;

		int i = 0;				// point to beginning
		int j = listLen - 2;	// point to element before the hidden pivot

		bool done = false
		while (false == done) {
			// move i if element is less than pivot and stop when an element >= pivot is found
			while (list[i] < pivot) i++;

			// move j if element is greater than pivot and stop when an element <= pivot is found
			while (list[j] > pivot) j--;

			// if i and j not crossed yet, swap the elements
			if (i < j) {
				uint32_t temp = list[j];
				list[j] = list[i];
				list[i] = temp;
			}
			else done = true;
		}

		// if crossed, restore pivot to position of i
		temp = list[i];
		list[i] = pivot;
		list[listLen - 1] = temp;
	
		// sort again the left and right
		if (i>1)
			sort(list, i);
	
		if ((i+1) < (listLen-1))
			sort(&list[i+1], listLen - i - 1);
	}
	
	return true;
}
	
