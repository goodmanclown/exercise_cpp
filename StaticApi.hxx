#include <stdint.h>

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

};


