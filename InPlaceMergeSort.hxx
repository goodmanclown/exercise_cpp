/**
 * class to do in place merge sort to ascending order
 * averge, worst, best case O(nlogn)
 */ 

#include <stdint.h>

class InPlaceMergeSort {

public:

	static void sort(uint32_t list[], uint32_t listLen);

	static void sort(uint32_t list[], uint32_t listLen, uint32_t tempList[]);

};


