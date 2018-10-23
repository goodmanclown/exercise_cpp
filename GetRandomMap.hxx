#include <stdint.h>
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::pair;


/**
 * class representing a data map to provide
 * add - no duplicate
 * delete
 * getRandom
 * at O(1)
 */ 

class GetRandomMap {

public:

    using MdnEndpoint = std::pair<uint64_t, uint64_t>;

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
     * @return true if add is OK.  false if duplicate
     */
    bool add(uint64_t min, uint64_t max);



    /**
     * delete a range with min and max
     *
     * @return true if remove is OK.  false if not found
     */
    bool remove(uint64_t min, uint64_t max);



    /**
     * get random
     *
     * @return true if output is valid.  false if empty
     */
    bool getRandom(MdnEndpoint& out) const;



    /**
     * find if the input range is in this map
     *
     * @return true if found.  false if not
     */
    bool find(uint64_t min, uint64_t max) const;


	/**
	 * use a map to keep track of the value and the position in the vector
	 */
	std::map<MdnEndpoint, std::size_t>   mMap;


	/**
	 * use a vector to keep the value
	 */
	std::vector<MdnEndpoint>             mVector;

};


