#include "StaticApi.hxx"

#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>

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
