#include "MergeSortV2.hxx"

#include <string.h>

// a temp list which is at least as large as the original list to be sorted and is assigned by the caller
// as a buffer to be reused in the merge
// this will eliminate the need to allocate temp list for each merge, assuming the merge is done in a single thread
uint32_t* MergeSortV2::tempList = 0;

MergeSortV2::MergeSortV2(uint32_t list[], uint32_t listLen)
{
	sortedListLen = listLen;
	sortedList = list;

	// swap the elements if needed
	if (listLen == 2) {
		if (list[0] > list[1]) {
			uint32_t temp = list[0];
			sortedList[0] = list[1];
			sortedList[1] = temp;
		}
	}
}


MergeSortV2::~MergeSortV2()
{
}


MergeSortV2 MergeSortV2::sort(uint32_t list[], uint32_t listLen)
{
	if (listLen <= 2) {
		MergeSortV2 sortedList(list, listLen);
		return sortedList;
	}
	else {
		// split the list into 2 halves, sort each half and merge them together
		uint32_t lenOfFirstHalf = listLen / 2;
		MergeSortV2 sortedList = sort(list, lenOfFirstHalf);
		sortedList += sort(&list[lenOfFirstHalf], listLen - lenOfFirstHalf);
		return sortedList;
	}
}


// the following logic assumed rhs.sortedList is the 2nd half of sortedList
MergeSortV2& MergeSortV2::operator+=(const MergeSortV2& rhs)
{
	uint32_t mergedListLen = sortedListLen + rhs.sortedListLen;

	// temp copy rhs list to the temp list
	memcpy(tempList, rhs.sortedList, rhs.sortedListLen*sizeof(uint32_t));

	int indexToSortedList1 = sortedListLen - 1;
	int indexToSortedList2 = rhs.sortedListLen - 1;
	for (int index = mergedListLen - 1; index >= 0; index--) {
		
		if (indexToSortedList1 >= 0 && indexToSortedList2 >= 0) {
			// both lists are not done
			if (sortedList[indexToSortedList1] > tempList[indexToSortedList2]) {
				// list1 value is smaller, insert list1 value
				sortedList[index] = sortedList[indexToSortedList1];
				indexToSortedList1--;
			}
			else if (sortedList[indexToSortedList1] < tempList[indexToSortedList2]) {
				// list2 value is smaller, insert list2 value
				sortedList[index] = tempList[indexToSortedList2];
				indexToSortedList2--;
			}
			else {
				// both are the same, insert list1 value first, then list2 value 
				sortedList[index] = sortedList[indexToSortedList1];
				indexToSortedList1--;
				index--;
				sortedList[index] = tempList[indexToSortedList2];
				indexToSortedList2--;
			}
		}
		else if (indexToSortedList1 >= 0 && indexToSortedList2 < 0) {
			// sortedList2 is already done
			// just insert list1 value
			sortedList[index] = sortedList[indexToSortedList1];
			indexToSortedList1--;
		}
		else if (indexToSortedList1 < 0 && indexToSortedList2 >= 0) {
			// sortedList1 is already done
			// just insert list2 value
			sortedList[index] = tempList[indexToSortedList2];
			indexToSortedList2--;
		}
	} // for (int index = mergedListLen - 1; index >=0; index--) {

	// now update the len of sorted list
	sortedListLen = mergedListLen;

	return *this;
}
	

MergeSortV2::MergeSortV2(const MergeSortV2& rhs)
{
	sortedListLen = rhs.sortedListLen;
	sortedList = rhs.sortedList;
}
	

MergeSortV2& MergeSortV2::operator=(const MergeSortV2& rhs)
{
	if (this == &rhs) return *this;

	sortedListLen = rhs.sortedListLen;
	sortedList = rhs.sortedList;

	return *this;
}
	

