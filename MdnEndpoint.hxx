#include <stdint.h>

/**
 * class representing a range of mdn and the associated endpoint
 */ 

class MdnEndpoint {

public:

	/**
	 * Constructor
	 *
	 */
	MdnEndpoint():mMin(0),mMax(0),mIndex(-1) { 
	};


	/**
	 * Constructor
	 *
	 * @param: min - min of mdn range
	 * @param: max - max of mdn range
	 *
	 */
	MdnEndpoint(uint64_t min, uint64_t max):mMin(min),mMax(max),mIndex(-1) { 
		// just in case min and max are swapped
		if (min > max) {
			mMin = max;
			mMax = min;
		}
	};


	/**
	 * Constructor
	 *
	 * @param: min - min of mdn range
	 *
	 */
	MdnEndpoint(uint64_t min):mMin(min),mMax(min),mIndex(-1) { };


			/**
			 * Copy Constructor
			 *
			 * @param: rhs - value to copied from
			 *
			 */
	MdnEndpoint(const MdnEndpoint& rhs) { mMin = rhs.mMin; mMax = rhs.mMax; mIndex = rhs.mIndex; };


			/**
			 * Destructor
			 */
	virtual ~MdnEndpoint() {};


			/**
			 * assign operator
			 *
			 * @param: rhs - value to copied from
			 *
			 */
	MdnEndpoint& operator=(const MdnEndpoint& rhs) { if (this == &rhs) return *this; mMin = rhs.mMin; mMax = rhs.mMax; mIndex = rhs.mIndex; return *this; };


			/**
			 * less than operator
			 *
			 * @param: rhs - value to compared with
			 *
			 * @return true if input mMin is greater than mMax
			 */
	bool operator<(const MdnEndpoint& rhs) const;


			/**
			 * greater than operator
			 *
			 * @param: rhs - value to compared with
			 *
			 * @return true if input mMax is less than mMin
			 */
	bool operator>(const MdnEndpoint& rhs) const;


			/**
			 * comparison operator
			 *
			 * @param: rhs - value to compared with
			 *
			 * @return true if input is same as this one
			 */
	bool operator==(const MdnEndpoint& rhs) const;


			/**
			 * Or' operator
			 *
			 * @param: rhs - value to OR' with
			 *
			 * @return value after OR' operator
			 */
	MdnEndpoint& operator|=(const MdnEndpoint& rhs);


			/**
			 * And operator
			 *
			 * @param: rhs - value to OR' with
			 *
			 * @return true if ranges are overlapped
			 */
	bool operator&(const MdnEndpoint& rhs);


			/**
			 * min of mdn range
			 */
	uint64_t	mMin;


			/**
			 * max of mdn range
			 */
	uint64_t	mMax;

			/**
			 * index to Endpoint list to retrieve the associated endpoint
			 */
	int	mIndex;
};


