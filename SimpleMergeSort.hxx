#include <stdint.h>

class SimpleMergeSort {

public:

	/**
	 * @return the merged list of the 2 input sorted lists
	 */
	static uint32_t* merge(const uint32_t sortedlist1[], uint32_t sortedlist1len, const uint32_t sortedlist2[], uint32_t sortedlist2len);
	
		
	/**
	 * @return true is the merge is ok
	 */
	static bool mergeInPlace(uint32_t sortedlist1[], uint32_t sortedlist1len, const uint32_t sortedlist2[], uint32_t sortedlist2len);
	
		
};


