#include "MergeSort.hxx"

#include <string.h>

MergeSort::MergeSort(const uint32_t list[], uint32_t listLen)
{
	sortedListLen = listLen;
	sortedList = new uint32_t[sortedListLen];

	if (listLen == 1) {
		sortedList[0] = list[0];
	}
	else if (listLen == 2) {
		if (list[0] > list[1]) {
			sortedList[0] = list[1];
			sortedList[1] = list[0];
		}
		else {
			sortedList[0] = list[0];
			sortedList[1] = list[1];
		}
	}
}


MergeSort::~MergeSort()
{
	if (sortedList) delete [] sortedList;
}


MergeSort MergeSort::sort(const uint32_t list[], uint32_t listLen)
{
	if (listLen <= 2) {
		MergeSort sortedList(list, listLen);
		return sortedList;
	}
	else {
		uint32_t lenOfFirstHalf = listLen / 2;
		MergeSort sortedList = sort(list, lenOfFirstHalf);
		sortedList += sort(&list[lenOfFirstHalf], listLen - lenOfFirstHalf);
		return sortedList;
	}
}


MergeSort& MergeSort::operator+=(const MergeSort& rhs)
{
	uint32_t mergedListLen = sortedListLen + rhs.sortedListLen;
	uint32_t* mergedList = new uint32_t[mergedListLen];

	int indexToSortedList1 = sortedListLen - 1;
	int indexToSortedList2 = rhs.sortedListLen - 1;
	for (int index = mergedListLen - 1; index >=0; index--) {
		
		if (indexToSortedList1 >= 0 && indexToSortedList2 >= 0) {
			// both lists are not done
			if (sortedList[indexToSortedList1] > rhs.sortedList[indexToSortedList2]) {
				// list1 value is smaller, insert list1 value
				mergedList[index] = sortedList[indexToSortedList1];
				indexToSortedList1--;
			}
			else if (sortedList[indexToSortedList1] < rhs.sortedList[indexToSortedList2]) {
				// list2 value is smaller, insert list2 value
				mergedList[index] = rhs.sortedList[indexToSortedList2];
				indexToSortedList2--;
			}
			else {
				// both are the same, insert list1 value first, then list2 value 
				mergedList[index] = sortedList[indexToSortedList1];
				indexToSortedList1--;
				index--;
				mergedList[index] = rhs.sortedList[indexToSortedList2];
				indexToSortedList2--;
			}
		}
		else if (indexToSortedList1 >= 0 && indexToSortedList2 < 0) {
			// sortedList2 is already done
			// just insert list1 value
			mergedList[index] = sortedList[indexToSortedList1];
			indexToSortedList1--;
		}
		else if (indexToSortedList1 < 0 && indexToSortedList2 >= 0) {
			// sortedList1 is already done
			// just insert list2 value
			mergedList[index] = rhs.sortedList[indexToSortedList2];
			indexToSortedList2--;
		}
	} // for (int index = mergedListLen - 1; index >=0; index--) {

	// remove the old list
	delete[] sortedList;

	sortedList = mergedList;
	sortedListLen = mergedListLen;

	return *this;
}
	

MergeSort::MergeSort(const MergeSort& rhs)
{
	sortedListLen = rhs.sortedListLen;
	sortedList = new uint32_t[sortedListLen];

	memcpy(sortedList, rhs.sortedList, sizeof(uint32_t)*sortedListLen);
}
	

MergeSort& MergeSort::operator=(const MergeSort& rhs)
{
	if (this == &rhs) return *this;

	delete[] sortedList;

	sortedListLen = rhs.sortedListLen;
	sortedList = new uint32_t[sortedListLen];

	memcpy(sortedList, rhs.sortedList, sizeof(uint32_t)*sortedListLen);

	return *this;
}
	

