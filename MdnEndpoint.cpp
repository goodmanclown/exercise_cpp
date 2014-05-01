#include "MdnEndpoint.hxx"


bool MdnEndpoint::operator<(const MdnEndpoint& rhs) const 
{ 
	if (this == &rhs) return false; 

	// if rhs min is greater than this max
	if (rhs.mMin > mMax) return true; 
	else return false; 
};

bool MdnEndpoint::operator>(const MdnEndpoint& rhs) const 
{ 
	if (this == &rhs) return false; 

	// if rhs max is less than this min
	if (rhs.mMax < mMin) return true; 
	else return false; 
};

bool MdnEndpoint::operator==(const MdnEndpoint& rhs) const
{
	if (this == &rhs) return true;

	// rhs is equal to this if rhs.mMin and rhs.mMax are both equal
	if (mMin == rhs.mMin && mMax == rhs.mMax) return true;

	return false;
}


MdnEndpoint& MdnEndpoint::operator|=(const MdnEndpoint& rhs)
{
	if (this == &rhs) return *this;

	// these 2 are ORed together by merging the range together
	if (mMin > rhs.mMin) mMin = rhs.mMin;

	if (mMax < rhs.mMax) mMax = rhs.mMax;

	return *this;
}


bool MdnEndpoint::operator&(const MdnEndpoint& rhs)
{
	if (this == &rhs) return true;

	if (mMin > rhs.mMax || mMax < rhs.mMin) return false;

	return true;
}
