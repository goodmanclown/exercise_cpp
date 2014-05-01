#include "InPlaceMergeSort.hxx"

#include <iostream>
#include <string.h>

using namespace std;

void InPlaceMergeSort::sort(uint32_t list[], uint32_t listLen)
{
	// if less than or equal to 1 element, nothing to sort
	if (listLen <= 1) return;

	// we need at most half of the list as extra space if we do merge in place
	uint32_t* tempList = new uint32_t[(listLen+1)/2];
	
	sort(list, listLen, tempList);

	delete [] tempList;
}


void InPlaceMergeSort::sort(uint32_t list[], uint32_t listLen, uint32_t tempList[])
{
	// if number is less than 1, do nothing
	if (listLen <= 1) 
		return;
	else if (listLen == 2) {
		// if only 2 elements left, swap them if needed
		if (list[0] > list[1]) {
			uint32_t temp = list[0];
			list[0] = list[1];
			list[1] = temp;
		}
	}
	else {
		// split the list into 2 and sort each half
		uint32_t indexToHalf = listLen / 2;
		uint32_t lenOf2ndHalf = listLen - indexToHalf;

		sort(list, indexToHalf, tempList);
		sort(&list[indexToHalf], lenOf2ndHalf, tempList);

		// merge the 2 sorted half together 
		
		// copy 2nd half onto temp list so the 2nd half of list 1 is empty space to use
		memcpy(tempList, &list[indexToHalf], lenOf2ndHalf*sizeof(uint32_t));

		int indexToSortedList1 = indexToHalf-1;
		int indexToSortedList2 = lenOf2ndHalf-1;
		
		// move from the back of each list and put the larger value at the end of the 1st list
		for (int index=listLen-1; index>=0; index--) {

         if (indexToSortedList1 >= 0 && indexToSortedList2 >= 0) {
				// both lists not done

				if (list[indexToSortedList1] > tempList[indexToSortedList2]) {
					list[index] = list[indexToSortedList1];
					indexToSortedList1--;
				}
				else if (list[indexToSortedList1] < tempList[indexToSortedList2]) {
					list[index] = tempList[indexToSortedList2];
					indexToSortedList2--;
				}
				else if (list[indexToSortedList1] == tempList[indexToSortedList2]) {
					list[index] = list[indexToSortedList1];
					indexToSortedList1--;
					index--;
					list[index] = tempList[indexToSortedList2];
					indexToSortedList2--;
				}
         }   
         else if (indexToSortedList1 >= 0 && indexToSortedList2 < 0) {
				// list1 is not done but list2 is done
				list[index] = list[indexToSortedList1];
				indexToSortedList1--;
			}
         else if (indexToSortedList1 < 0 && indexToSortedList2 >= 0) {
				// list1 is done but list2 is not done
				list[index] = tempList[indexToSortedList2];
				indexToSortedList2--;
			}
      } // for (int index=listLen-1; index>=0; index--) {
	}	// else {
}

