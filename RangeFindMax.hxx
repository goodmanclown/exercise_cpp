#include <stdint.h>

#include <vector>

/**
 * class to find the max number of occurrences in an array of pairs of integers
 */ 
class RangeFindMax {

public:

	/** 
     * Constructor
	 */
	RangeFindMax(const std::vector<std::pair<int, int>>& input):mRange(input) {};


	/** 
     * Destructor
	 */
	~RangeFindMax() {};


	/**
	 * @return integer with max number of occurrences
	 */
	int find();


private:

	/** 
     * Constructor
	 */
	RangeFindMax(const RangeFindMax& rhs)=delete;



	/** 
     * assignment operator
	 */
	RangeFindMax& operator=(const RangeFindMax& rhs)=delete;

   
    const std::vector<std::pair<int, int>>& mRange;
};


