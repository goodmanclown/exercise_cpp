/**
 * template function to do binary search in a sorted array
 * the type of input array must implement operator< and operator==
 */ 

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <utility>

using std::advance;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::find_if_not;

class BinarySearch {

public:

	/**
	 * @param inputElem - an array of <T> to be searched
	 * @param startIndex - index to the input array to start searching from
	 * @param endIndex - index to the input array to stop searching 
	 * @param value - value to be searched in the array
     *
	 * @return index of value in the array if the value is found. -1 if not.
	 */
	template <typename T>
	static int search(const T inputElem[], uint32_t startIndex, uint32_t endIndex, T value)
	{
		cout << " start " << startIndex << " end " << endIndex << endl;

		// if input is empty, do nothing
		uint32_t numOfInputElem = endIndex + 1 - startIndex;
		if (0 >= numOfInputElem) return -1;

		// if input has only 1 element, just compare and return the comparison result
		
        if (1 == numOfInputElem) 
        {
			if (inputElem[startIndex] == value) return startIndex;
			else return -1;
		}

		if (2 == numOfInputElem) 
        {
			if (inputElem[endIndex] == value) return endIndex;
			else if (inputElem[startIndex] == value) return startIndex;
			else return -1;
		}

		// found the index to the middle of the input array
		uint32_t indexToHalf = numOfInputElem / 2;

		if (value < inputElem[startIndex+indexToHalf]) 
        {
			// search the value in the 1st half of the array
			cout << " search 1st half" << endl;
			return search(inputElem, startIndex, startIndex+indexToHalf-1, value);
		}
		else 
        {
			// search the value in the 2nd half of the array
			cout << " search 2nd half" << endl;
			return search(inputElem, startIndex+indexToHalf, endIndex, value);
		}
	}

/**
Given an array of integers nums sorted in ascending order, find the starting and ending position 
of a given target value.

If target is not found in the array, return [-1, -1].

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Example 3:

Input: nums = [], target = 0
Output: [-1,-1]
 

Constraints:

0 <= nums.length <= 10**5
-10**9 <= nums[i] <= 10**9    
nums is a non-decreasing array.
-10**9 <= target <= 10**9

*/

    static pair<int, int> searchRange(const std::vector<int>& nums, int target) 
    {
        if (nums.empty()) return { -1, -1 };

        size_t endIndex = nums.size() - 1;
        int targetStartIndex = search<int>(nums.data(), 0, endIndex, target);
        
        // target does not appear
        if (targetStartIndex < 0) return { -1, -1 };
        
        // assume no duplicate
        size_t targetEndIndex = targetStartIndex;

        if (targetStartIndex != 0)
        {
            // search backward until the target is not found
            for (int sIndex = targetStartIndex - 1; sIndex > 0; --sIndex)
            {
                if (nums.at(sIndex) != target) break;
                
                targetStartIndex = sIndex;
            } 
        }

        if (targetEndIndex != endIndex)
        {
            // search forward until the target is not found
            auto begIter = nums.cbegin();
            advance(begIter, targetEndIndex+1);
            auto endIter = nums.cbegin();
            advance(endIter, endIndex+1);
            find_if_not(begIter, endIter,
                [&target, &targetEndIndex] (const auto& entry)
                {
                    if (entry != target) return false;
                
                    ++targetEndIndex;

                    return true;
                }
            );
        }

        cout << " targetStartIndex " << targetStartIndex << ", " << targetEndIndex << endl;

        return { targetStartIndex, targetEndIndex };
    }
};


