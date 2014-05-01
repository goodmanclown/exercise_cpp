/**
 * from the input dn, find the associated endpoint
 */ 

#include "MdnEndpoint.hxx"

#include <list>
#include <string>
#include <vector>

using namespace std;


class FindEndpointByMdn
{
public:

	typedef unsigned int uInt;

	/**
    * Constructor
	 */
	FindEndpointByMdn() { mMdnEndpointList.clear(); mMidpoint = mMdnEndpointList.end(); mEndpointList.clear(); };

	
	/**
	 * Destructor
	 */
	virtual ~FindEndpointByMdn() { mMdnEndpointList.clear(); mEndpointList.clear(); };


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
	typedef vector<string>	EndpointList;
	EndpointList		mEndpointList;


	/**
	 * a list of MdnEndpoint
	 */
	typedef list<MdnEndpoint>	MdnEndpointList;
	MdnEndpointList	mMdnEndpointList;

   /**
	 * mid point of the list
    */
	typedef MdnEndpointList::iterator  MepListIter;
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
	 * @return index to EndPointList storing the input
	 *
	 */
	int find(const char endpoint[]) const;



};


