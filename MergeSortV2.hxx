#include <stdint.h>


class MergeSortV2 {

public:

	/**
	 * @return an object of a merged list
	 */
	static MergeSortV2 sort(uint32_t list[], uint32_t listlen);

	MergeSortV2(uint32_t list[], uint32_t listlen);

	virtual ~MergeSortV2();
		
	/**
	 * return use Copy Constructor
	 */
	MergeSortV2(const MergeSortV2& rhs);

	uint32_t* sortedList;

	uint32_t	sortedListLen;

	static uint32_t* tempList;
		
private:

	/**
	 * @return an object of a merged list
	 */
	MergeSortV2& operator+=(const MergeSortV2&);
	
	/**
	 * @return an object of a merged list
	 */
	MergeSortV2& operator=(const MergeSortV2&);
	
};


