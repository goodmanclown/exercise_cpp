#include "MergeSort.hxx"


bool MergeSort::merge(uint32_t sortedList1[], uint32_t sortedList1Len, const uint32_t sortedList2[], uint32_t sortedList2Len)
{
	if (sortedList1Len == 0 && sortedList2Len == 0) return false;

	if (sortedList1Len <= sortedList2Len) return false;

	// list 1 have enough space at the end to accommodate the elements of list 2
	uint32_t mergedListLen = sortedList1Len;
	sortedList1Len = mergedListLen - sortedList2Len;

	int indexToSortedList1 = sortedList1Len - 1;
	int indexToSortedList2 = sortedList2Len - 1;
	for (int index = mergedListLen - 1; index >=0; index--) {
		
		if (indexToSortedList1 >= 0 && indexToSortedList2 >= 0) {
			// both lists are not done
			if (sortedList1[indexToSortedList1] > sortedList2[indexToSortedList2]) {
				// list1 value is smaller, insert list1 value
				sortedList1[index] = sortedList1[indexToSortedList1];
				indexToSortedList1--;
			}
			else if (sortedList1[indexToSortedList1] < sortedList2[indexToSortedList2]) {
				// list2 value is smaller, insert list2 value
				sortedList1[index] = sortedList2[indexToSortedList2];
				indexToSortedList2--;
			}
			else {
				// both are the same, insert list1 value first, then list2 value 
				sortedList1[index] = sortedList1[indexToSortedList1];
				indexToSortedList1--;
				index--;
				sortedList1[index] = sortedList2[indexToSortedList2];
				indexToSortedList2--;
			}
		}
		else if (indexToSortedList1 >= 0 && indexToSortedList2 < 0) {
			// sortedList2 is already done
			// just insert list1 value
			sortedList1[index] = sortedList1[indexToSortedList1];
			indexToSortedList1--;
		}
		else if (indexToSortedList1 < 0 && indexToSortedList2 >= 0) {
			// sortedList1 is already done
			// just insert list2 value
			sortedList1[index] = sortedList2[indexToSortedList2];
			indexToSortedList2--;
		}
	} // for (int index = mergedListLen - 1; index >=0; index--) {

	return true;
}
	

