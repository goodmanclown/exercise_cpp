#include <stdint.h>

#include <vector>
#include <string>

/**
 * class to output the look and say sequence
 */ 
class StaticApi {

public:

	/**
	 * @param level of look and say sequence
	 * @@parama vector of string representing the sequence
	 */
	static std::size_t lookAndSay(uint32_t level, std::vector<std::string>& output);


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

};


