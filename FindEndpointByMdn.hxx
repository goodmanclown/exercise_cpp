#include "MdnEndpoint.hxx"

#include <list>
#include <string>
#include <vector>

using namespace std;


/**
 * from the input dn, find the associated endpoint
 */ 
class FindEndpointByMdn
{
public:

	using uInt = unsigned int;

	/**
    * Constructor
	 */
	FindEndpointByMdn():mMidpoint(mMdnEndpointList.end()) { };

	
	/**
	 * Destructor
	 */
	virtual ~FindEndpointByMdn()=default;


	/**
	 *
	 * @param: min - min of mdn range
	 * @param: max - max of mdn range
	 * @param: endpoint - a string of endpoint
    *
	 * @return true if add ok
	 *
	 */
	bool add(uInt min, uInt max, const char endpoint[]);


	/**
	 *
	 * @param: mdn - look up the endpoint
	 *
	 * @return a string of the endpoint
	 */
	const string& find(uInt mdn);


	/**
	 *
	 * @param: endpoint - a string of endpoint
	 * 
	 * @return index to EndPointList storing the input
	 *
	 */
	int add(const char endpoint[]);


	/**
	 * a vector of EndPoint
	 */
	using EndpointList = vector<string>;
	EndpointList		mEndpointList;


	/**
	 * a list of MdnEndpoint
	 */
	using MdnEndpointList = list<MdnEndpoint>;
	MdnEndpointList	mMdnEndpointList;

   /**
	 * mid point of the list
    */
	using MepListIter = MdnEndpointList::iterator;
	MepListIter 	mMidpoint;


private:


	/**
	 *
	 * @param: min - min of mdn range
	 * @param: max - max of mdn range
	 * @param: outIter - iterator to the element in the list if find.  otherwise, end()
     * @return 0 - sucess, -1 - overlapped
	 */
	int find(uInt min, uInt max, MepListIter& outIter);


	/**
	 *
	 * @param: endpoint - a string of endpoint
	 * 
     * @return 0 - sucess, -1 - not found
	 *
	 */
	int find(const char endpoint[]) const;



};


