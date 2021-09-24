#include "StaticApi.hxx"
#include "BinarySearchTree.hxx"

#include <unistd.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <list>
#include <sstream>
#include <map>
#include <unordered_map>
#include <utility>

using namespace std;

vector<string> StaticApi::lookAndSay(uint32_t level)
{
    vector<string> output;

    ostringstream buf;

    if (level == 0) {
        return move(output);
    }

    if (level == 1) {

        buf << 1;

        cout << buf.str() << endl;

        output.push_back(buf.str());

        return move(output);
	}

    output = lookAndSay(level - 1);

    if (output.empty())
    {
        return move(output);
    }

	// get the last entry in the output
    string& str = output.back();

    char curChar = str[0];
    size_t count = 1;
    for_each (++str.cbegin(), str.cend(),
        [&](const char& ch) 
        {
            cout << ch << endl;

            if (curChar == ch) 
            {
                // if same numeral, count it
                ++count;
	        }
            else
            {
                buf << count;
                buf << curChar;

                cout << buf.str() << endl;

                // update the current char to count
                curChar = ch;
                count = 1;
            }
        }
    );

    // append with the count of last char
    buf << count;
    buf << curChar;

    cout << buf.str() << endl;

    output.push_back(buf.str());

	return move(output);
}


void StaticApi::productOfA1(int arrayA[], size_t sizeA, int arrayB[], size_t sizeB)
{
    // input size is 0, just return
    if (sizeA == 0 || sizeB == 0 || sizeA != sizeB) return;

    // populate each element of B
    for (size_t indexB = 0; indexB < sizeB; ++indexB) {
        // loop through each element of A
        long long product = 1;
        for (size_t indexA = 0; indexA < sizeA; ++indexA) {
            if (indexB != indexA) {
                product *= arrayA[indexA];
            }
        }

        // check and make sure there's no overflow
        if (INT32_MAX >= product && product >= (-INT32_MAX-1)) {
            arrayB[indexB] = product;
        }
    }
}


void StaticApi::productOfA2(int arrayA[], size_t sizeA, int arrayB[], size_t sizeB)
{
    // input size is 0, just return
    if (sizeA == 0 || sizeB == 0 || sizeA != sizeB) return;

    // first compute the product of all elements of a
    
    // loop through each element of A
    long long product = 1;
    for (size_t indexA = 0; indexA < sizeA; ++indexA) {
        product *= arrayA[indexA];
    }

    // populate each element of B
    for (size_t indexB = 0; indexB < sizeB; ++indexB) {
 
        // take out the value of element of A at indexB
        long long result;
        if (arrayA[indexB] != 0) {
            result = product / arrayA[indexB];
        }
        else result = 0;

        // check and make sure there's no overflow
        if (INT32_MAX >= result && result >= (-INT32_MAX-1)) {
            arrayB[indexB] = result;
        }
    }
}


size_t StaticApi::searchStringInArray(string arrayString[], size_t sizeArray, size_t indexOffset, const string& target)
{
    if (sizeArray == 0) return string::npos;

    if (target.empty()) return string::npos;

    // divide the array in half
    size_t midIndex = sizeArray / 2;

    // move the midInex to the first non-empty string in the array
    while (midIndex > 0 && arrayString[midIndex].empty())
    {
        --midIndex;
    }

    if (arrayString[midIndex] == target)
    {   // matched
        return midIndex+indexOffset; 
    }
    else if (arrayString[midIndex] < target)
    {   // less than
        return searchStringInArray(arrayString, midIndex, 0, target);
    }
    else if ((sizeArray - midIndex) > 0)
    {   // greater than
        return searchStringInArray(&arrayString[midIndex+1], sizeArray - midIndex, midIndex, target);
    }

    return string::npos;
}


bool StaticApi::findElementInMatrix(int matrix[], std::size_t numRow, std::size_t numCol, int target)
{
    // compare against the min and max
    size_t elementIndex = 0;
 
    size_t row = 0;
    int col = 0;

    // get the min element
    elementIndex = row*numCol + col;

    if (target < matrix[elementIndex]) return false;

    // get the max element
    row = numRow-1;
    col = numCol-1;

    elementIndex = row*numCol + col;
 
    if (target > matrix[elementIndex]) return false;

    // now look for the element in the matrix
    // start with the upper right corner of the matrix
    row = 0;
    col = numCol - 1;
    while ( row < numRow && col >= 0 )
    {
        elementIndex = row*numCol + col;

        if (target == matrix[elementIndex]) return true;

        if (target < matrix[elementIndex])
        {
            --col;
        }
        else
        {
            ++row;
        }
    }

    return false;
}


int StaticApi::findIntegerWithMostOccurrences(const std::vector<std::pair<int, int>>& input)
{
	unordered_map<int, size_t> result;

	for_each (input.cbegin(), input.cend(), 
        [&](const std::pair<int, int>& value) {

		    // count each value in the range with the map 
		    for (int i = value.first; i <= value.second; ++i) 
            {
			    result[i]++;
		    }
        }
    );
	
	// go through each entry in the map and find the max value
	int ret = 0;
	uint32_t maxCount = 0;

	for_each ( result.cbegin(), result.cend(),
        [&](const pair<int, size_t>& value) {

		    // remember the integer if the count is higher
		    cout << "first " << value.first << ", second " << value.second << endl;

		    if (value.second > maxCount) 
            {
			    // remember the int
			    ret = value.first;

		        // remember the max
			    maxCount = value.second;
		    }
        }
	);

	return ret;
}


vector<vector<uint32_t>> StaticApi::findTargetSumCombination(uint32_t input[], uint32_t uLength, uint32_t uTargetSum)
{
    map<uint32_t, size_t> sortMap;
    
    // populate the set with the input entry 
    for (size_t index = 0; index < uLength; ++index)
    {
        ++sortMap[input[index]];
    }

    // populate the input with the entries sorted
    size_t index = 0;
    for_each(sortMap.cbegin(), sortMap.cend(), 
        [&](auto& entry) 
        {
            size_t occurrences = entry.second;
            while (occurrences > 0)
            {
                input[index++] = entry.first;
                --occurrences;
            }
        }
    );

    return findTargetSumCombinationTemp(input, uLength, uTargetSum);
}


vector<vector<uint32_t>> StaticApi::findTargetSumCombinationTemp(uint32_t input[], uint32_t uLength, uint32_t uTargetSum)
{
    vector<vector<uint32_t>> vResult;

    if (uLength == 0)
    {
        return vResult;
    }
    
    // accumulate the input
    uint32_t sum = 0;
    for (size_t index=0; index < uLength; ++index)
    {
        cout << input[index] << ",";
        sum += input[index];
    }

    cout << endl;

    if (sum == uTargetSum)
    {   // copy the input to the result
        for (size_t index=0; index < uLength; ++index)
        {
            vector<uint32_t> vResultTmp(input, input+uLength);
            vResult.push_back(move(vResultTmp));

            return vResult;
        }
    }

    if (uLength > 2 && sum > uTargetSum)
    {
        // if greater, get the result from the sub-array
        for (uint32_t index=0; index < uLength; ++index) 
        {
        	if (index != 0) 
            {
        		// swap first integer with the integer at the index
			    auto temp = input[index];
			    input[index] = input[0];
			    input[0] = temp;
            }

    		auto vResultTmp = findTargetSumCombinationTemp(&input[1], uLength-1, uTargetSum);

            if (!vResultTmp.empty())
            {
                vResult.insert(vResult.end(), vResultTmp.begin(), vResultTmp.end());
            }

		    if (index != 0) 
            {
			    // restore the first integer with the integer at the index
			    auto temp = input[index];
			    input[index] = input[0];
			    input[0] = temp;
            }
        }
	} 

    return vResult;
}

bool StaticApi::IsPalindrome(const int input)
{
    if (!input) return false;

    array<char, 10> aSplitDigit = { };

    size_t index = 0;
    int tmpInput = input;
    while (tmpInput)
    {
        aSplitDigit[index] = tmpInput % 10;

        tmpInput = tmpInput / 10;
        ++index;
    }

    for (size_t fIndex = 0, bIndex = index-1; fIndex < bIndex; ++fIndex, --bIndex)
    {
        if (aSplitDigit[fIndex] != aSplitDigit[bIndex]) return false;
    }

    return true;
}


int StaticApi::findClosestNumber(int target, const int input[], size_t sizeOfInput)
{
    auto lastSmallestDiff = abs( abs(target) - abs(input[0]) );
    int result = input[0];

    for (size_t indexToInput = 1; indexToInput < sizeOfInput; ++indexToInput)
    {
        auto tmpDiff = abs( abs(target) - abs(input[indexToInput]) );
        if (tmpDiff <= lastSmallestDiff)
        {
            lastSmallestDiff = tmpDiff;
            result = input[indexToInput];
        }
    }

    return result;
}

int StaticApi::findMaxPointsOnLine(const vector<pair<int, int>>& points) {

    int maxNumOfPoints = 1;

    // going up to the right diagonal
    for (size_t index = 0; index < points.size(); ++index) {

        const auto& startCoord = points[index];
        int numOfPoints = 1;
        
        pair<int, int> nextDiagCoord = make_pair<int, int>(startCoord.first + 1, startCoord.second + 1);

        bool bDone = false;
        while (bDone == false) {

            // going horizontal and find the next point
            size_t index1 = 0;
            for (; index1 < points.size(); ++index1) {

                const auto& entry = points[index1];
                if (nextDiagCoord == entry) {
                    ++numOfPoints;

                    nextDiagCoord = make_pair<int, int>(entry.first + 1, entry.second + 1);
                    break;
                }
            }

            if (index1 >= points.size()) {
                bDone = true;
            }
        }

        if (maxNumOfPoints < numOfPoints) {
            maxNumOfPoints = numOfPoints;
        }
    }

    // going down to the left diagonal
    for (size_t index = 0; index < points.size(); ++index) {

        const auto& startCoord = points[index];
        int numOfPoints = 1;
        
        pair<int, int> nextDiagCoord = make_pair<int, int>(startCoord.first + 1, startCoord.second - 1);

        bool bDone = false;
        while (bDone == false) {

            // going horizontal and find the next point
            size_t index1 = 0;
            for (; index1 < points.size(); ++index1) {

                const auto& entry = points[index1];
                if (nextDiagCoord == entry) {
                    ++numOfPoints;

                    nextDiagCoord = make_pair<int, int>(entry.first + 1, entry.second - 1);
                    break;
                }
            }

            if (index1 >= points.size()) {
                bDone = true;
            }
        }

        if (maxNumOfPoints < numOfPoints) {
            maxNumOfPoints = numOfPoints;
        }
    }

    return maxNumOfPoints;
}

vector<int> StaticApi::sortByNumberLengthMap(const vector<int>& nums)
{ 
    vector<int> result;

    if (nums.empty()) return result;

    map<size_t, vector<int>> numByLength;

    // define a map to store the numbers in the input vector sorted by length
    for_each(nums.cbegin(), nums.cend(),
        [&numByLength](const auto& entry)
        {
            auto quotient = entry / 10;
            auto count = 1;
            while (quotient != 0)
            {
                quotient = quotient / 10;
                ++count;
            }

            numByLength[count].push_back(entry);
        }
    );

    // now go thru the map and put the numbers in each index to the result array
    for (const auto& kvp : numByLength)
    {
        copy(kvp.second.cbegin(), kvp.second.cend(), back_inserter(result));
    }

    return result;
}

vector<int> StaticApi::sortByNumberLengthList(const vector<int>& nums)
{ 
    vector<int> result;

    if (nums.empty()) return result;

    // define a lambda to return the length of a number
    auto findNumLength = [](const int& entry) -> size_t
        {
            auto quotient = entry / 10;
            auto numLength = 1;
            while (quotient != 0)
            {
                quotient = quotient / 10;
                ++numLength;
            }

            return numLength;
        };

    // define a list to store the numbers in the input vector
    list<int> numByLength(nums.cbegin(), nums.cend());

    // now sort the list by the length of number, and maintain the order 
    auto outIterEnd = numByLength.end();
    --outIterEnd;
    for (auto outIter = numByLength.begin(); outIter != outIterEnd; ++outIter )
    {
        auto minNum = *outIter;
        auto minIter = outIter;

        auto inIter = outIter;
        ++inIter;
        for (; inIter != numByLength.end(); ++inIter)
        {
            if (findNumLength(minNum) > findNumLength(*inIter))
            {
                minNum = *inIter;
                minIter = inIter;
            }
        }

        if (outIter != minIter)
        {
            // move minIter to the front of outIter
            numByLength.insert(outIter, *minIter);
            numByLength.erase(minIter);
        }
    }

    // now copy the list to the result
    copy(numByLength.cbegin(), numByLength.cend(), back_inserter(result));

    return result;
}


uint StaticApi::maxArea(const vector<uint>& height)
{
    if (height.empty()) return 0;

    uint resultMaxArea = 0;
    for (size_t indexOuterLoop = 0; indexOuterLoop < height.size() - 1; ++indexOuterLoop)
    {
        auto yAxis = height[indexOuterLoop];

        for (size_t indexInnerLoop = indexOuterLoop + 1; indexInnerLoop < height.size(); ++indexInnerLoop)
        {
            if (height[indexInnerLoop] >= yAxis)
            {  // this vertical line can be the opposite side of the container with height of yAxis
               // calculate the area upto this line

        	    cout << "y " << yAxis << ", x " << (indexInnerLoop - indexOuterLoop) << endl;

                auto tmpMaxArea = yAxis * (indexInnerLoop - indexOuterLoop);

                if (tmpMaxArea > resultMaxArea)
                {
                    resultMaxArea = tmpMaxArea;
                }
            }
            else
            {  // reduce the height of the container to this vertical line
               // calculate the area upto this line

        	    cout << "y " << height[indexInnerLoop] << ", x " << (indexInnerLoop - indexOuterLoop) << endl;
               
                auto tmpMaxArea = height[indexInnerLoop] * (indexInnerLoop - indexOuterLoop);

                if (tmpMaxArea > resultMaxArea)
                {
                    resultMaxArea = tmpMaxArea;
                }
            }
        }
    }

    return resultMaxArea;
}


vector<pair<uint, uint>> StaticApi::merge(const vector<pair<uint, uint>>& intervals)
{
    vector<pair<uint, uint>> result;

    if (intervals.empty()) return result;

    if (intervals.size() == 1) return intervals;

    auto iter = intervals.cbegin();

    // first - start
    // second - end
    auto lastInterval = *iter;

    for_each (++iter, intervals.cend(), 
        [&lastInterval, &result](const auto& entry)
        {
            if (entry.first <= lastInterval.second)
            {   // overlapped
                lastInterval.second = entry.second;
            }
            else
            {   // non-overlapped
                result.emplace_back(lastInterval);

                // update to the non-overlapped interval
                lastInterval = entry;
            }
        }
    );

    result.emplace_back(lastInterval);

    return result;
}


 int StaticApi::firstMissingPositive(const std::vector<int>& nums)
 {
    if (nums.size() < 3) return -1;

    // go through the input and find the smallest and largest positive numbers
    int smallest = 0;
    int largest = 0;

    for_each(nums.cbegin(), nums.cend(), 
        [&smallest, &largest](const auto& entry)
        {
            // ignore negative number
            if (entry < 0) return;

            if (entry < smallest) smallest = entry;

            if (entry > largest) largest = entry;
        }
    );

    // now use the smallest and the largest to construct a vector 
    // initialize the vector to -1
    vector<int> tmpNums;
    tmpNums.resize(largest-smallest+1);
    fill(tmpNums.begin(), tmpNums.end(), -1);

    // go through the input array and zero the entry using the input as index
    for (const auto& entry : nums)
    {
        size_t indexToTmpNums = entry - smallest;
        tmpNums[indexToTmpNums] = 0;
    }

    // go through the tmp array to look for the first index with a -1
    for (size_t index; index < tmpNums.size(); ++index)
    {
        if (tmpNums[index] == -1)
        {
            return smallest+index;
        } 
    }

    return -1;
 }


 string StaticApi::intToRomanUsingArray(int num) 
 {
    static array<string, 10> onesArray =
        { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

    static array<string, 10> tensArray =
        { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };

    static array<string, 10> hundredsArray =
        { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };

    static array<string, 10> thousandsArray =
        { "", "M", "MM", "MMM", "", "", "", "", "", "" };

    string convertedRomanString;

    // just return if out of bound
    if (num <= 0 || num > 3999) return convertedRomanString;

    int placeIndex = 1;
    while (num > 0)
    {
        int value = num % 10;

        switch (placeIndex)
        {
            case 1:
                convertedRomanString = onesArray[value] + convertedRomanString;
            break;
            
            case 2:
                convertedRomanString = tensArray[value] + convertedRomanString;
            break;

            case 3:
                convertedRomanString = hundredsArray[value] + convertedRomanString;
            break;

            case 4:
                convertedRomanString = thousandsArray[value] + convertedRomanString;
            break;
        }

        num = num / 10;

        ++placeIndex;
    }

    return convertedRomanString;
 }

string StaticApi::intToRomanUsingLambda(int num) 
{
    auto intToRomanLessThanFour = [](int num, const string& symbol) 
    {
        string convertedRomanString;

        if (num < 0) return convertedRomanString;
        
        for (int i = 0; i < num; ++i)
        {
            convertedRomanString += symbol;    
        }

        return convertedRomanString;
    };

    string convertedRomanString;

    // just return if out of bound
    if (num <= 0 || num > 3999) return convertedRomanString;

    int placeIndex = 1;
    while (num > 0)
    {
        int value = num % 10;

        switch (placeIndex)
        {
            case 1:
            {
                if (value < 4)
                {
                    convertedRomanString = intToRomanLessThanFour(value, "I") + convertedRomanString;
                }
                else if (value == 4)
                {
                    convertedRomanString = "IV" + convertedRomanString;
                }
                else if (value == 5)
                {
                    convertedRomanString = "V" + convertedRomanString;
                }
                else if (value < 9)
                {
                    convertedRomanString = "V" + intToRomanLessThanFour(value - 5, "I") + convertedRomanString;
                }
                else if (value == 9)
                {
                    convertedRomanString = "IX" + convertedRomanString;
                }
            }
            break;
            
            case 2:
            {
                if (value < 4)
                {
                    convertedRomanString = intToRomanLessThanFour(value, "X") + convertedRomanString;
                }
                else if (value == 4)
                {
                    convertedRomanString = "XL" + convertedRomanString;
                }
                else if (value == 5)
                {
                    convertedRomanString = "L" + convertedRomanString;
                }
                else if (value < 9)
                {
                    convertedRomanString = "L" + intToRomanLessThanFour(value - 5, "X") + convertedRomanString;
                }
                else if (value == 9)
                {
                    convertedRomanString = "XC" + convertedRomanString;
                }
            }
            break;

            case 3:
            {
                if (value < 4)
                {
                    convertedRomanString = intToRomanLessThanFour(value, "C") + convertedRomanString;
                }
                else if (value == 4)
                {
                    convertedRomanString = "CD" + convertedRomanString;
                }
                else if (value == 5)
                {
                    convertedRomanString = "D" + convertedRomanString;
                }
                else if (value < 9)
                {
                    convertedRomanString = "D" + intToRomanLessThanFour(value - 5, "C") + convertedRomanString;
                }
                else if (value == 9)
                {
                    convertedRomanString = "CM" + convertedRomanString;
                }
            }
            break;

            case 4:
            {
                if (value < 4)
                {
                    convertedRomanString = intToRomanLessThanFour(value, "M") + convertedRomanString;
                }
            }
            break;
        }

        num = num / 10;

        ++placeIndex;
    }

    return convertedRomanString;
 }