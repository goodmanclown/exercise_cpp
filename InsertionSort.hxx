/**
 * class to do insertion sort to ascending order
 * average and worse case O(n^2)
 * best case O(n) when the list is in descending order
 */ 

#include <stdint.h>

class InsertionSort {

public:

	static void sort(uint32_t list[], uint32_t listLen);


	static void move(uint32_t list[], uint32_t startIndex, uint32_t endIndex);
};


