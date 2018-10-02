#include "RangeFindMax.hxx"

#include <unistd.h>
#include <iostream>
#include <map>

using namespace std;

int RangeFindMax::find()
{
	map<int, uint32_t> result;

	for (size_t index = 0; index < mRange.size(); ++index) {

		// get the first pair from the array
		pair<int, int> value = mRange[index];
		int valueFirst = value.first;
		int valueSecond = value.second;

		// count each value in the range with the map 
		for (int i = valueFirst; i <= valueSecond; i++) {
			result[i]++;
		}
	}
	
	// go through each entry in the map and find the max value
	int ret = 0;
	uint32_t maxCount = 0;

	map<int, uint32_t>::const_iterator cIter = result.cbegin();
	for ( ; cIter != result.cend(); ++cIter) {

		// if the count if higher
		cout << "first " << cIter->first << ", second " << cIter->second << endl;

		if (cIter->second > maxCount) {
			// remember the int
			ret = cIter->first;

		    // remember the max
			maxCount = cIter->second;
		}
	}

	return ret;
}

