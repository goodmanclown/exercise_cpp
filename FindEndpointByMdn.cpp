#include "FindEndpointByMdn.hxx"

#include <iostream>

bool FindEndpointByMdn::add(uInt min, uInt max, const char endpoint[])
{
	MepListIter outIter;
	int ret = find(min, max, outIter);

	if (-1 == ret) return false;	// overlap not allowed

	if (outIter == mMdnEndpointList.end()) {
		// input not found
		MdnEndpoint mep(min, max);

		// add the endpoint to the list
		int index = add(endpoint);
		mep.mIndex = index;

		if (mMidpoint == mMdnEndpointList.end()) {
			// if midpoint is at the end, only when the list is empty
			// insert before it
			mMdnEndpointList.push_front(mep);

			// move up midpoint to the beginning
			mMidpoint = mMdnEndpointList.begin();
		
			return true;
		}	// if (mMidpoint == mMdnEndpointList.end()) {
		else {
			// search for the lower bound
			if (mep < *mMidpoint) {
				if (mMidpoint == mMdnEndpointList.begin()) {
					// if midpoint is at the beginning
					// insert before it
					mMdnEndpointList.push_front(mep);

					return true;
				}
				else {
					// if smaller than search from begin to midpoint
					MepListIter iter = mMdnEndpointList.begin();
					for (; iter != mMidpoint; ++iter) {
						if (mep < *iter) {
							// insert before it
							mMdnEndpointList.insert(iter, mep);

							// move up midpoint, if not already 1 element away from beginning
							MepListIter tempIter = mMidpoint;
							--tempIter;
							if (mMdnEndpointList.begin() != tempIter) 
								mMidpoint = tempIter;

							return true;
						}		
					}
				}
			} 	// if (mep < *mMidpoint) {
			else {
				// if not smaller, than search from midpoint to end
				MepListIter iter = mMidpoint;
				for (; iter != mMdnEndpointList.end(); ++iter) {
					if (mep < *iter) {
						// insert before it
						mMdnEndpointList.insert(iter, mep);

						// move down midpoint, if not already 1 element away from the end
						MepListIter tempIter = mMidpoint;
						++tempIter;	// get to the next element
						++tempIter;	// get to the element after next
						if (mMdnEndpointList.end() != tempIter) 
							++mMidpoint;

						return true;
					}
				}

				// if we reach here, the element to be inserted is greater 
				// than all in the list
				// just append it
				mMdnEndpointList.push_back(mep);

				MepListIter tempIter = mMidpoint;
				++tempIter;	// get to the next element
				++tempIter;	// get to the element after next
				if (mMdnEndpointList.end() != tempIter) 
					++mMidpoint;

				return true;
			}
		}
	}	// if (outIter == mMdnEndpointList.end()) {

	return false;
}


int FindEndpointByMdn::add(const char endpoint[])
{
	// make sure this endpoint is not already added
	int i = find(endpoint);

	if (-1 != i) return i;

	// add the endpoint to the list
	mEndpointList.push_back(endpoint);
	return mEndpointList.size()-1;
}


int FindEndpointByMdn::find(uInt min, uInt max, MepListIter& outIter)
{
	if (!mMdnEndpointList.size()) {
		outIter = mMdnEndpointList.end();
		return 0;
	}

	MdnEndpoint mep(min, max);

	if (mep < *mMidpoint) {
		// if smaller, than search from begin to midpoint
		MepListIter iter = mMdnEndpointList.begin();
		for (; iter != mMidpoint; ++iter) {
			if (mep == *iter) {
				outIter = iter;
				return 0;		
			}
			if (mep & *iter) return -1;		// found an overlap
		}
	}
	else {
		// if not smaller, than search from midpoint to end
		MepListIter iter = mMidpoint;
		for (; iter != mMdnEndpointList.end(); ++iter) {
			if (mep == *iter) {
				outIter = iter;
				return 0;		
			}
			if (mep & *iter) return -1;		// found an overlap
		}
	}

	outIter = mMdnEndpointList.end();
	return 0;
}

int FindEndpointByMdn::find(const char endpoint[]) const
{
	if (!mEndpointList.size()) return -1;

	// make sure this endpoint is not already added
	if (mEndpointList.size()) {
		uInt size = mEndpointList.size();
		for (uInt i=0; i < size; i++) {
			if (endpoint == mEndpointList[i]) return i;
		}
	}

	return -1;
}
