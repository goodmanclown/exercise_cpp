#include "StaticApi.hxx"
#include "BinarySearchTree.hxx"

#include <unistd.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
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
    for_each(sortMap.cbegin(), sortMap.cend(), 
        [&input, index = 0] (auto& entry) mutable
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

    map<size_t, vector<int>> sortByLength;

    for (const auto& entry : nums)
    {
        auto len = findNumLength(entry);

        sortByLength[len].push_back(entry);
    }

    // now copy the list to the result
    for (const auto& kvp : sortByLength)
    {
        for (const auto& entry : kvp.second)
        {
            result.push_back(entry);
        }
    }

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
    auto intToRomanOnes = [](int num, const string& symbol)
    {
        string convertedRomanString;

        if (num < 0) return convertedRomanString;
        
        for (int i = 0; i < num; ++i)
        {
            convertedRomanString += symbol;    
        }

        return convertedRomanString;
    };

    auto intToRomanHelper = [](int num, 
                                const string& symbolOne, 
                                const string& symbolFive, 
                                const string& symbolTen,
                                function<string(int, string)> intToRomanOnesApi)
    {
        string convertedRomanString;

        if (num < 4)
        {
            convertedRomanString = intToRomanOnesApi(num, symbolOne) + convertedRomanString;
        }
        else if (num == 4)
        {
            convertedRomanString = symbolOne + symbolFive + convertedRomanString;
        }
        else if (num == 5)
        {
            convertedRomanString = symbolFive + convertedRomanString;
        }
        else if (num < 9)
        {
            convertedRomanString = symbolFive + intToRomanOnesApi(num - 5, symbolOne) + convertedRomanString;
        }
        else if (num == 9)
        {
           convertedRomanString = symbolOne + symbolTen + convertedRomanString;
        }

        return convertedRomanString;
    };

    array<tuple<string, string, string>, 4> symbol {
        {
            tuple<string, string, string>( "I", "V", "X" ),
            tuple<string, string, string>( "X", "L", "C" ),
            tuple<string, string, string>( "C", "D", "M" ),
            tuple<string, string, string>( "M", "", "" )
        }
    };

    string convertedRomanString;

    // just return if out of bound
    if (num <= 0 || num > 3999) return convertedRomanString;

    int placeIndex = 0;
    while (num > 0)
    {
        string symbolOne;
        string symbolFive;
        string symbolTen;
        tie(symbolOne, symbolFive, symbolTen) = symbol[placeIndex++];

        convertedRomanString = intToRomanHelper(num %10, symbolOne, symbolFive, symbolTen, 
                                intToRomanOnes) + 
                                convertedRomanString;

        num = num / 10;
    }

    return convertedRomanString;
}


 string StaticApi::intToWrittenUsingArray(int sNum) 
 {
    static array<string, 10> onesArray =
        { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    static array<string, 10> teensArray =
        { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };

    static array<string, 10> tensArray =
        { "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };

    static array<string, 10> placeArray =
        { "", "", "hundred", "thousand", "thousand", "hundred thousand", "million", "million", "hundred million", "billion" };

    string convertedWrittenString;

    // remmber the sign of the input
    bool neg = (sNum < 0);

    // work with positive value of the input
    uint num = (sNum > 0) ? sNum : -sNum;

    if (num > 9999999999) return convertedWrittenString;

    if (num == 0) 
    {
        return "zero";
    }

    // first go through the number, single out the digits and find the max place
    int maxPlaceIndex = 0;
    std::stack<uint> digitStack;
    while (num > 0)
    {
        // single out the digit
        uint digit = num % 10;

        // save the digit
        digitStack.push(digit);

        num = num / 10;

        ++maxPlaceIndex;
    }

    uint lastValue = 0;
    int placeIndex = maxPlaceIndex;
    while (!digitStack.empty())
    {
        uint value = digitStack.top();
        digitStack.pop();

        switch (placeIndex)
        {
            case 1:
            case 4:
            {
                if (lastValue < 1)
                {
                    if (value)
                    {
                        convertedWrittenString = !convertedWrittenString.empty() 
                                            ? convertedWrittenString + " and " + onesArray[value] + 
                                                                            (!placeArray[placeIndex-1].empty() 
                                                                            ? " " + placeArray[placeIndex-1]
                                                                            : placeArray[placeIndex-1])
                                            : onesArray[value] + 
                                                        (!placeArray[placeIndex-1].empty() 
                                                        ? " " + placeArray[placeIndex-1]
                                                        : placeArray[placeIndex-1]);
                    }
                }
                else if (lastValue == 1)
                {
                    if (value)
                    {
                        convertedWrittenString = !convertedWrittenString.empty() 
                                                ? convertedWrittenString + " " + teensArray[value] + 
                                                                            (!placeArray[placeIndex-1].empty() 
                                                                            ? " " + placeArray[placeIndex-1]
                                                                            : placeArray[placeIndex-1])
                                                : teensArray[value] + 
                                                        (!placeArray[placeIndex-1].empty() 
                                                        ? " " + placeArray[placeIndex-1]
                                                        : placeArray[placeIndex-1]);
                    }
                }
                else if (lastValue > 1)
                {
                    if (value)
                    {
                        // form the written string
                        convertedWrittenString = !convertedWrittenString.empty() 
                                                ? convertedWrittenString + " " + onesArray[value] + 
                                                                            (!placeArray[placeIndex-1].empty() 
                                                                            ? " " + placeArray[placeIndex-1]
                                                                            : placeArray[placeIndex-1])
                                                : onesArray[value] + 
                                                        (!placeArray[placeIndex-1].empty() 
                                                        ? " " + placeArray[placeIndex-1]
                                                        : placeArray[placeIndex-1]);
                    }
                }

                // remember the value
                lastValue = value;
            }
            break;
            
            case 2:
            case 5:
            {
                if (value > 1)
                {
                    convertedWrittenString = !convertedWrittenString.empty() 
                                                ? convertedWrittenString + " " + tensArray[value]
                                                : tensArray[value];
                }

                // remember the value
                lastValue = value;
            }
            break;

            case 3:
            {
                if (lastValue < 1)
                {
                    if (value)
                    {
                        convertedWrittenString = !convertedWrittenString.empty() 
                                            ? convertedWrittenString + " and " + onesArray[value] + " " + placeArray[placeIndex-1]
                                            : onesArray[value] + " " + placeArray[placeIndex-1];
                    }
                }
                else 
                {
                    if (value)
                    {
                        // form the written string
                        convertedWrittenString = !convertedWrittenString.empty() 
                                                ? convertedWrittenString + " " + onesArray[value] + " " + placeArray[placeIndex-1]
                                                : onesArray[value] + " " + placeArray[placeIndex-1];
                    }
                }

                // remember the value
                lastValue = value;
            }
            break;
        }

        --placeIndex;
    }

    if (neg != true)
    {
        return convertedWrittenString;
    }
    else
    {
        return "negative " + convertedWrittenString;
    }
}



vector<string> StaticApi::restoreValidIPAddress(const std::string& digitString)
{
    if (digitString.empty() == true) return {};

    return restoreValidIPAddressRecursive(4, digitString, "");
}

vector<string> StaticApi::restoreValidIPAddressRecursive(size_t minDigits, const string& digitString, const string& prefix)
{
    if (digitString.length() < minDigits) return {};

    if (minDigits == 1)
    {
        if (digitString.length() == 1 || 
            (digitString.length() > 1 && digitString.at(0) != '0' && stoi(digitString) <= 255))
        {
            return { prefix + "." + digitString };
        }

        return {};
    }

    vector<string> validIPAddressVec;

    for (size_t subStrLen = 1; subStrLen < digitString.length(); ++subStrLen)
    {
        auto validIPAddress = digitString.substr(0, subStrLen);

        if (stoi(validIPAddress) > 255) break;

        if (prefix.empty() != true)
        {
            validIPAddress = prefix + "." + validIPAddress;
        }
        
        auto ret = restoreValidIPAddressRecursive(minDigits - 1, digitString.substr(subStrLen), validIPAddress);
        if (ret.empty() != true)
        {
            validIPAddressVec.insert(validIPAddressVec.begin(), ret.begin(), ret.end());
        }

        if (digitString.at(0) == '0')
        {   // 0 is only valid by itself
            break;
        }
    }

    return validIPAddressVec;
}


list<int> StaticApi::sortList(list<int>& head)
{
    if (head.empty() == true) return { };

    if (head.size() == 1) return head;

    if (head.size() == 2) 
    {
        auto temp = head.front();
        if (temp > head.back())
        {   // just swap
            head.pop_front();
            head.push_back(temp);
        }
    }
    
    for (auto outIter = head.begin(); outIter != head.end(); )
    {
        auto inIter = outIter;

        bool swapped = false;
        for (++inIter; inIter != head.end() && swapped == false; )
        {
            if (*outIter > *inIter)
            {
                swapped = true;
                auto temp = *outIter;
                outIter = head.erase(outIter);
                ++inIter;
                head.insert(inIter, temp);
                break;
            }
            
            ++inIter;
        }

        if (swapped == false)
        {
            ++outIter;
        }
    }

    return head;
}

bool StaticApi::canJump(const std::vector<int>& nums)
{
    if (nums.empty()) return false;

    size_t lastIndex = nums.size() - 1;
    size_t landedIndex = 0;
    for (size_t index = 0; index < nums.size(); ++index)
    {
        const auto& entry = nums.at(index);

        // invalid input
        if (entry < 0) return false;

        if (landedIndex < lastIndex)
        {   // we are not yet at the last index
            // but can't jump anymore
            if (entry == 0) return false;

            landedIndex += entry;
        }

        if (landedIndex == lastIndex)
        {   // landed
            return true;
        }
        else if (landedIndex > lastIndex)
        {   // jumped past the last Index
            return false;
        }
    }

    return false;
}

std::vector<int> StaticApi::rotate(const std::vector<int>& nums, uint32_t k)
{
    // nothing to roate
    if (nums.empty() || nums.size() == 1 || k == 0) return nums;

    std::vector<int> result;

    // find the iterator from the back
    result.insert(result.begin(), nums.end()-k, nums.end());

    result.insert(result.end(), nums.begin(), nums.end()-k-1);

    return result;
}

size_t StaticApi::removeDuplicates(vector<int>& nums)
{
    if (nums.empty()) return 0;

    auto iter = nums.begin();
    int iLastNums = *iter;
    uint8_t uDuplicateCount = 1;
    ++iter;
    while (iter != nums.end())
    {
        if (*iter != iLastNums)
        {
            iLastNums = *iter;
            uDuplicateCount = 1;
            ++iter;
            continue;
        }

        ++uDuplicateCount;

        if (uDuplicateCount > 2)
        {   // erase the entry
            iter = nums.erase(iter);

            --uDuplicateCount;
        }
        else
        {
            ++iter;
        }
    }

    return nums.size();
}

int StaticApi::numRescueBoats(vector<int>& people, size_t limit) 
{
    if (people.empty()) return 0;

    if (people.size() > 5 * 10000) return -1;

    if (limit == 0 || limit > 3 * 10000) return -1; 

    size_t numBoats = 0;
    for (size_t indexOuter = 0; indexOuter < people.size()-1; ++indexOuter)
    {
        if (people[indexOuter] < 0)
        {   // data already used, go to the next one
            continue;
        }

        size_t indexInner = indexOuter+1;
        size_t targetIndexInner = indexInner;
        int diffMin = -1;
        for (; indexInner < people.size(); ++indexInner) 
        {
            if (people[indexInner] < 0)
            {   // data already used, go to the next one
                continue;
            }

            auto tempSum = people[indexOuter] + people[indexInner];
            if (tempSum <= limit && (diffMin == -1 || diffMin > (limit - tempSum)))
            {
                targetIndexInner = indexInner;
                diffMin = limit - tempSum;
            }
        }

        if (diffMin >= 0)
        {
            // take this pair of outer and inner index
            ++numBoats;

            // invalidate the data
            people[indexOuter] = -1;
            people[targetIndexInner] = -1;
        }
        else
        {
            // take this outer index
            ++numBoats;

            // invalidate the data
            people[indexOuter] = -1;
        }
    }

    if (people[people.size()-1] > 0)
    {   // the last one has not be removed
        ++numBoats;
    }

    return numBoats;
}


uint StaticApi::findMaxPickedFruits(std::vector<uint>& fruits)
{
    uint uMaxPickedFruits = 0;

    // if input is empty, just return
    if (fruits.empty())
    {
        return uMaxPickedFruits;
    }

    // keep track of the number of type of fruits in the basket
    uint uNumFruitTypeInBasket = 0;

    // define a map with the key as the type of fruits and value the number of fruits of the type
    unordered_map<uint, uint> basket;

    // go through the input array
    for (size_t outIndex = 0; outIndex < fruits.size(); ++outIndex)
    {
        for (size_t inIndex = outIndex; inIndex < fruits.size(); ++inIndex)
        {
            // get the type of fruit
            auto type = fruits[inIndex];
            
            if (basket.find(type) != basket.cend())
            {   // this is an old type
                // just upcount
                ++(basket[type]);
            }
            else if (uNumFruitTypeInBasket < 2)
            {   // we still have space
                // this is a new type
                // just add to the basket
                basket[type] = 1;

                // remember the number of fruit types in the basket
                ++uNumFruitTypeInBasket;
            }
            else
            {   // no more space in our basket
                break;
            }
        }

        // find the number of fruits picked
        size_t numPickedFruits = 0;
        for (const auto& entry : basket)
        {
            numPickedFruits += entry.second;
        }

        // do we have more fruits this time
        if (numPickedFruits > uMaxPickedFruits)
        {   
           uMaxPickedFruits = numPickedFruits;
        }

        // clear the buffer and try again
        uNumFruitTypeInBasket = 0;
        basket.clear();
    }

    return uMaxPickedFruits;
}



vector<string> StaticApi::letterCombinations(const string& digits)
{
    static const u_char MAX_NUM_DIGIT = 8;
    static const u_char MAX_NUM_CHARACTER = 4;

    // define a 2-dimensional array to keep the mapping of digits to characters
    static array<array<string, MAX_NUM_CHARACTER>, MAX_NUM_DIGIT> digitToCharArray = {
        {
            { { "a", "b", "c", "" } },
            { { "d", "e", "f", "" } },
            { { "g", "h", "i", "" } },
            { { "j", "k", "l", "" } },
            { { "m", "n", "o", "" } },
            { { "p", "q", "r", "s" } },
            { { "t", "u", "v", "" } },
            { { "w", "x", "y", "z" } }
        }
    };

    vector<string> result;

    if (digits.empty() || digits.size() >= 4) 
    {   // out of bound, just return
        return result;
    }

    // if there is only 1 digit, just return the corresponding mapping
    if (digits.size() == 1)
    {
        char digit = digits[0];

        char digitIndex = digit - '2';

        if (digitIndex < 0 || digitIndex > 7) 
        {
            // out of bound, just return
            return result;
        }

        const auto& chars = digitToCharArray[digitIndex];

        for (const auto& cstr : chars)
        {   // save to result
            if (!cstr.empty())
            {
                result.push_back(cstr);
            }
        }
    }
    else 
    {
        for (size_t outIndex = 0; outIndex < MAX_NUM_DIGIT-1; ++outIndex)
        {
            char digit = digits[0];

            char digitIndex = digit - '2';

            if (digitIndex < 0 || digitIndex > 7) 
            {
                // out of bound, just return
                return result;
            }

            const auto& chars = digitToCharArray[digitIndex];

        }
    }

    return result;
}