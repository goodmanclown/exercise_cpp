#include <stdint.h>

#include <list>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

/**
 * class to output the look and say sequence
 */ 
class StaticApi {

public:

	/**
	 * @param level of look and say sequence
	 * @@parama vector of string representing the sequence
	 */
	static std::vector<std::string> lookAndSay(uint32_t level);


	/**
	 * @param arrayA - an array of integers
	 * @param arrayB - an array of integers such that B[i] is the product of all A[j], where i != j
	 */
	static void productOfA1(int arrayA[], size_t sizeA, int arrayB[], size_t sizeB);


	/**
	 * @param arrayA - an array of integers
	 * @param arrayB - an array of integers such that B[i] is the product of all A[j], where i != j
	 */
	static void productOfA2(int arrayA[], size_t sizeA, int arrayB[], size_t sizeB);


	/**
	 * @param arrayString - an array of strings
	 * @param sizeArray - size of the array of strings
	 * @param indexOffset - offset to be added to the index of matched string in the subarray
	 * @param target - target string to be found in the array
	 */
	static std::size_t searchStringInArray(std::string arrayString[], std::size_t sizeArray, std::size_t indexOffset, const std::string& target);


	/**
	 * @param matrix - a matrix of M x N integer
	 * @param numRow - number of row
	 * @param numCol - number of col
	 * @param target - target integer to be found in the matrix
	 */
	static bool findElementInMatrix(int matrix[], std::size_t numRow, std::size_t numCol, int target);


	/**
	 * @param input - a vector of a pair of integers
	 * 
	 * @return integer with the most number of occurrences 
	 */
    static int findIntegerWithMostOccurrences(const std::vector<std::pair<int, int>>& input);

	/**
	 * @param input - a vector of integers
	 * 
	 * @return largest difference
	 */
    template<size_t SIZE>
    static uint32_t findLargestDifference(const std::array<int, SIZE>& input)
    {
        if (input.empty())
        {
            return 0;
        }

        auto uLargestDiff = 0;

        auto cIter = input.rbegin();
        auto uLargestElement = *cIter;

        for_each(++cIter, input.rend(),
            [&](auto& element)
            {
                auto uTempDiff = abs(uLargestElement - element);

                if (uTempDiff > uLargestDiff)
                {
			        uLargestDiff = uTempDiff;
		        }

                if (element > uLargestElement)
                {   // find a new largest element
                    uLargestElement = element;
                }
            }
        );

    	return uLargestDiff;
    }

	/**
	 * @param input - a vector of integers
	 * @param uTargetSum - sum to be matched
	 * 
	 * @return true if uTargetSum is found
	 */
    static bool findTargetSum(const uint32_t input[], size_t inputSize, uint32_t uTargetSum)
    {
        if (inputSize < 2)
        {
            return false;
        }

        for (auto uIndexToArray = 0u; uIndexToArray < inputSize; ++uIndexToArray)
        {
            auto tmpSum = input[uIndexToArray];

            for (auto uInnerIndex = uIndexToArray+1; uInnerIndex < inputSize; ++uInnerIndex)
            {
                tmpSum += input[uInnerIndex];
                if (tmpSum == uTargetSum)
                {
                    return true;
                }
            }
        }

    	return false;
    }

	/**
	 * @param input - an array of integers
     * @param total - total number to be distributed
	 * 
	 * @return 
	 */
    template<size_t SIZE>
    static void distributeTotal(std::array<size_t, SIZE>& output, uint32_t uTotal)
    {
        if (!uTotal)
        {
            return;
        }

        auto uNthRoud = 0u;
        auto uIndexToArray = 0u;
        do 
        {
            auto uGiveToEachIndex = uNthRoud*SIZE + uIndexToArray + 1;

            if (uTotal >= uGiveToEachIndex)
            {
                output[uIndexToArray] += uGiveToEachIndex;

                uTotal -= uGiveToEachIndex;

                ++uIndexToArray;
                if (uIndexToArray >= SIZE)
                {
                    uIndexToArray = 0;
                    ++uNthRoud;
                }
            }
            else
            {
                output[uIndexToArray] += uTotal;

                uTotal -= uTotal;
            }
        } 
        while (uTotal > 0);

    	return;
    }

	/**
	 * @param input - a vector of integers
	 * 
	 * @return a set of combinations
	 */
    static std::vector<std::vector<uint32_t>> findTargetSumCombination(uint32_t input[], 
        uint32_t uLength, uint32_t uTargetSum);

	/**
	 * @param input - an integer value
	 * 
	 * @return true if input is a palindrome
	 */
    static bool IsPalindrome(const int input);

	/**
	 * @param target - target vallue to search for 
	 * @param input - array of integer 
	 * 
	 * @return closest value to target
	 */
    static int findClosestNumber(int target, const int input[], size_t sizeOfInput);


    /**
     * Given n points on a 2D plane, find the maximum number of points that lie on the 
     * same straight line.
     *
Example 1:

Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o  
+------------->
0  1  2  3  4
Example 2:

Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
     *
     */
    static int findMaxPointsOnLine(const std::vector<std::pair<int, int>>& points);

    /**
Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].

You need to return the number of important reverse pairs in the given array.

Example1:

Input: [1,3,2,3,1]
Output: 2

Example2:

Input: [2,4,3,5,1]
Output: 3

Note:
The length of the given array will not exceed 50,000.
All the numbers in the input array are in the range of 32-bit integer.
     */ 
    // static int findImportantReversePairs(const std::vector<int>& nums);


    /**
Create a sorting function which sorts numbers not by numerical order, but by number length! This means sorting 
numbers with the least amount of digits first, up to the numbers with the most digits.

numberLenSort([1, 54, 1, 2, 463, 2]) ➞ [1, 1, 2, 2, 54, 463]

numberLenSort([999, 421, 22, 990, 32]) ➞ [22, 32, 999, 421, 990]

numberLenSort([9, 8, 7, 6, 5, 4, 31, 2, 1, 3]) ➞ [9, 8, 7, 6, 5, 4, 2, 1, 3, 31]

If two numbers have the same number of digits, return them in the order they first appeared (this makes it 
different to just sorting the numbers normally).
     */ 
    static std::vector<int> sortByNumberLengthMap(const std::vector<int>& nums);

    static std::vector<int> sortByNumberLengthList(const std::vector<int>& nums);


    /**
Given n pairs of parentheses, write a function to generate all combinations of well-formed 
parentheses.

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
 

Constraints:

1 <= n <= 8
     */ 
    // static std::vector<std::string> generateParenthesis(uint n);


/**
Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate 
(i, ai). n vertical lines are drawn such that the two endpoints of the line i is at (i, ai) 
and (i, 0). Find two lines, which, together with the x-axis forms a container, such that the 
container contains the most water.

Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this 
case, the max area of water (blue section) the container can contain is 49 (9-2)*7.

Input: height = [1,1]
Output: 1

Input: height = [4,3,2,1,4]
Output: 16

Input: height = [1,2,1]
Output: 2
 */

    static uint maxArea(const std::vector<uint>& height);


/**
 Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping 
 intervals, and return an array of the non-overlapping intervals that cover all the intervals 
 in the input.

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 

Constraints:

1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104
 */
    static std::vector<std::pair<uint, uint>> merge(const std::vector<std::pair<uint, uint>>& intervals);



/**
Given an unsorted integer array nums, find the smallest missing positive integer.

 

Example 1:

Input: nums = [1,2,0]
Output: 3
Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
 

Constraints:

0 <= nums.length <= 300
-231 <= nums[i] <= 231 - 1
 */

    int firstMissingPositive(const std::vector<int>& nums);

/**
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two one's added together. 12 is written as XII, 
which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four 
is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it 
making four. The same principle applies to the number nine, which is written as IX. There are six instances 
where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given an integer, convert it to a roman numeral.

 

Example 1:

Input: num = 3
Output: "III"
Example 2:

Input: num = 4
Output: "IV"
Example 3:

Input: num = 9
Output: "IX"
Example 4:

Input: num = 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.
Example 5:

Input: num = 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 

Constraints:

1 <= num <= 3999
 */
    static std::string intToRomanUsingArray(int num);

    static std::string intToRomanUsingLambda(int num);

    static std::list<int> sortList(std::list<int>& head);
/**
Given a string s containing only digits, return all possible valid IP addresses that can be obtained from s. You can return them in any order.

A valid IP address consists of exactly four integers, each integer is between 0 and 255, separated by single dots and cannot have leading zeros. For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses and "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses. 

 

Example 1:

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
Example 2:

Input: s = "0000"
Output: ["0.0.0.0"]
Example 3:

Input: s = "1111"
Output: ["1.1.1.1"]
Example 4:

Input: s = "010010"
Output: ["0.10.0.10","0.100.1.0"]
Example 5:

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 

Constraints:

0 <= s.length <= 3000
s consists of digits only.
 */
    static std::vector<std::string> restoreValidIPAddress(const std::string& digitString);

/**
You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

Example 1:

Input: nums = [1,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 105
 */
    static bool canJump(const std::vector<int>& nums);

/**
Given an array, rotate the array to the right by k steps, where k is non-negative.

 

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
 

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
0 <= k <= 105
 */
    static std::vector<int> rotate(const std::vector<int>& nums, uint32_t k);


private:

	/** 
     * Constructor
	 */
	StaticApi()=delete;


	/** 
     * Destructor
	 */
	~StaticApi()=delete;


	/** 
     * Constructor
	 */
	StaticApi(const StaticApi& rhs)=delete;



	/** 
     * assignment operator
	 */
	StaticApi& operator=(const StaticApi& rhs)=delete;


	/**
	 * @param input - a vector of integers, sorted
	 * 
	 * @return a set of combinations
	 */
    static std::vector<std::vector<uint32_t>> findTargetSumCombinationTemp(uint32_t input[], 
        uint32_t uLength, uint32_t uTargetSum);

    static std::string generateParenthesisRecursive(uint n, std::string prefix);

    static std::vector<std::string> restoreValidIPAddressRecursive(size_t minDigits, const std::string& digitString, const std::string& prefix);
};


