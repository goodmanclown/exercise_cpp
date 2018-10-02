#include "MdnEndpoint.hxx"

#include <stdint.h>
#include <map>
#include <vector>

using std::map;
using std::vector;


/**
 * class representing a data map to provide
 * add - no duplicate
 * delete
 * getRandom
 * at O(1)
 */ 

class GetRandomMap {

public:

	/**
	 * Constructor
	 *
	 */
	GetRandomMap()=default;


	/**
	 * Destructor
	 */
	virtual ~GetRandomMap()=default;


    /**
     * add a range with min and max
     *
     * @return true if add is OK.  fail if duplicate
     */
    bool add(uint64_t min, uint64_t max);



    /**
     * delete a range with min and max
     *
     * @return true if remove is OK.  fail if not found
     */
    bool remove(uint64_t min, uint64_t max);



    /**
     * get random
     *
     * @return true if output is valid.  false if empty
     */
    bool getRandom(uint64_t& min, uint64_t& max);



	/**
	 * use a map to keep track of the value and the position in the vector
	 */
	std::map<MdnEndpoint, std::size_t>   mMap;


	/**
	 * use a vector to keep the value
	 */
	std::vector<MdnEndpoint>             mVector;

};


