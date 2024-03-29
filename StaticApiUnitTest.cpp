// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.
//
// Author: wan@google.com (Zhanyong Wan)


// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:


// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "StaticApi.hxx"

#include "gtest/gtest.h"


using namespace std;

// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>


// Tests StaticApi().

TEST(StaticApi, LookAndSayLevelOne) {

	vector<string> output = StaticApi::lookAndSay(1);

    EXPECT_EQ(output.size(), 1);
    EXPECT_EQ(output[0], "1");

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, lookAndSayLevelTwo) {

	vector<string> output = StaticApi::lookAndSay(2);

    EXPECT_EQ(output.size(), 2);
    EXPECT_EQ(output[0], "1");
    EXPECT_EQ(output[1], "11");

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, lookAndSayLevelThree) {

	vector<string> output = StaticApi::lookAndSay(3);

    EXPECT_EQ(output.size(), 3);
    EXPECT_EQ(output[0], "1");
    EXPECT_EQ(output[1], "11");
    EXPECT_EQ(output[2], "21");

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, lookAndSayLevelFour) {

	vector<string> output = StaticApi::lookAndSay(4);

    EXPECT_EQ(output.size(), 4);
    EXPECT_EQ(output[0], "1");
    EXPECT_EQ(output[1], "11");
    EXPECT_EQ(output[2], "21");
    EXPECT_EQ(output[3], "1211");

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, lookAndSayLevelFive) {

	vector<string> output = StaticApi::lookAndSay(5);

    EXPECT_EQ(output.size(), 5);
    EXPECT_EQ(output[0], "1");
    EXPECT_EQ(output[1], "11");
    EXPECT_EQ(output[2], "21");
    EXPECT_EQ(output[3], "1211");

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, productOfA1) {

	int a[4] = { 2, 1, 5, 9 };
    int b[4] = { 0, 0, 0, 0 };

	StaticApi::productOfA1(a, 4, b, 4);

    EXPECT_EQ(b[0], 45);
    EXPECT_EQ(b[1], 90);
    EXPECT_EQ(b[2], 18);
    EXPECT_EQ(b[3], 10);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, productOfA2) {

	int a[4] = { 2, 1, 5, 9 };
    int b[4] = { 0, 0, 0, 0 };

	StaticApi::productOfA2(a, 4, b, 4);

    EXPECT_EQ(b[0], 45);
    EXPECT_EQ(b[1], 90);
    EXPECT_EQ(b[2], 18);
    EXPECT_EQ(b[3], 10);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, searchStringInArrayMatch) {

	string a[] = { "at", "", "", "", "", "ball", "", "", "car", "", "", "dad", "", "" };

	size_t ret = StaticApi::searchStringInArray(a, 14, 0, "ball");

    EXPECT_EQ(ret, 5);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, searchStringInArrayUnMatch) {

	string a[] = { "at", "", "", "", "", "ball", "", "", "car", "", "", "dad", "", "" };

	size_t ret = StaticApi::searchStringInArray(a, 14, 0, "ballcat");

    EXPECT_EQ(ret, string::npos);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, findElementInMatrixMatch)
{
	int matrix[][5] = 
    { 
        { 1, 2, 3, 4, 5 },
        { 2, 4, 6, 8, 10 },
        { 3, 6, 9, 12, 15 },
        { 4, 8, 12, 16, 20 }
    };

    int* pMatrix = &matrix[0][0];
	bool ret = StaticApi::findElementInMatrix(pMatrix, 4, 5, 9);

    EXPECT_TRUE(ret);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, findElementInMatrixNoMatch)
{
	int matrix[][5] = 
    { 
        { 1, 2, 3, 4, 5 },
        { 2, 4, 6, 8, 10 },
        { 3, 6, 9, 12, 15 },
        { 4, 8, 12, 16, 20 }
    };

    int* pMatrix = &matrix[0][0];
	bool ret = StaticApi::findElementInMatrix(pMatrix, 4, 5, 13);

    EXPECT_FALSE(ret);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, findIntegerWithMostOccurrences) {

	vector<pair<int, int>> input;

	input.push_back(pair<int, int>(1,2));
	input.push_back(pair<int, int>(-1,1));

	int ret = StaticApi::findIntegerWithMostOccurrences(input);

    EXPECT_EQ(ret, 1);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, findLargestDifference) {

	array<int, 8> input = {1, 2, 3, 0, 4, -10, 5, -11};

	int ret = StaticApi::findLargestDifference<input.size()>(input);

    EXPECT_EQ(ret, 16);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, findLargestDifferenceEmpty) {

	array<int, 0> input;

	uint32_t ret = StaticApi::findLargestDifference<input.size()>(input);

    EXPECT_EQ(ret, 0);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, findLargestDifferenceOneElement) {

	array<int, 1> input = { 5 };

	uint32_t ret = StaticApi::findLargestDifference<input.size()>(input);

    EXPECT_EQ(ret, 0);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, findTargetSumCombination) {

    uint32_t input[] = { 1, 2, 1, 3 };

	auto ret = StaticApi::findTargetSumCombination(input, 4, 4);

    EXPECT_EQ(ret.size(), 5);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, distributeTotal) {

    array<size_t, 4> expectOutput = { 8, 8, 10, 12 };

    array<size_t, 4> output = { 0, 0, 0, 0 };

	StaticApi::distributeTotal<output.size()>(output, 38);

    EXPECT_EQ(output, expectOutput);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests FindTargetSum()
class FindTargetSumTestFixture : public ::testing::Test {
    public:

        FindTargetSumTestFixture() = default;

        ~FindTargetSumTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 3u;

        std::array<bool, TEST_SIZE> expectResult{ { false, true, true } };

        std::array<uint32_t, TEST_SIZE> inputTarget{ {10, 4, 5 } };

        const uint32_t input[7] = { 1, 0, 1, 2, 1 };

        void GetExpect(const std::array<bool, TEST_SIZE>& result)
        {
            EXPECT_EQ(result, expectResult);
        }
};

// Tests member api insert
TEST_F(FindTargetSumTestFixture, FindTargetSumTestFixture) {

    auto index = 0u;
    std::array<bool, TEST_SIZE> result = { };

    for ( auto& entry : inputTarget )
    {
        result[index++] = StaticApi::findTargetSum(input, sizeof(input), entry);
    }

    GetExpect(result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}


// Tests StaticApi().

TEST(StaticApi, IsPalindromeaZero) {

	auto result = StaticApi::IsPalindrome(0);

    EXPECT_FALSE(result);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests StaticApi().

TEST(StaticApi, IsPalindromeIntMax) {

	auto result = StaticApi::IsPalindrome(2147483647);

    EXPECT_FALSE(result);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

TEST(StaticApi, IsPalindromeIntMin) {

	auto result = StaticApi::IsPalindrome(-2147483648);

    EXPECT_FALSE(result);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

TEST(StaticApi, IsPalindromeEvenDigits) {

	auto result = StaticApi::IsPalindrome(1221);

    EXPECT_TRUE(result);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

TEST(StaticApi, IsPalindromeOddDigits) {

	auto result = StaticApi::IsPalindrome(-1234321);

    EXPECT_TRUE(result);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests TimedHashMap()
class FindClosestTargetTestFixture : public ::testing::Test {
    public:

        FindClosestTargetTestFixture() = default;

        ~FindClosestTargetTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 3u;

        std::array<int, TEST_SIZE> result = { };

        std::array<int, TEST_SIZE> expectResult{ { 5, 9, 5 } };

        std::array<int, TEST_SIZE> inputTarget{ {5, 11, 4 } };

        const int input[7] = { 2, 5, 6, 7, 8, 8, 9 };

        void GetExpect(const std::array<int, TEST_SIZE>& expect)
        {
            EXPECT_EQ(result, expect);
        }
};

// Tests member api insert
TEST_F(FindClosestTargetTestFixture, findClosestTarget) {

    auto index = 0u;
    for ( auto& entry : inputTarget )
    {
        result[index++] = StaticApi::findClosestNumber(entry, input, sizeof(input));
    }

    GetExpect(expectResult);

    char cmsg[] = { '1', '2', 0 };

    short s = reinterpret_cast<short>(cmsg);

    printf("\n\n0x%x, short 0x%x\n\n", cmsg, s);


  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}


// Tests maxNumPointsOnLine()
class FindMaxNumOfPointsOnLineTestFixture : public ::testing::Test {
    public:

        FindMaxNumOfPointsOnLineTestFixture() = default;

        ~FindMaxNumOfPointsOnLineTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 2u;

        array<vector<pair<int, int>>, TEST_SIZE> inputTarget {
            { 
                { pair<int, int>(1, 1), pair<int, int>(2, 2), pair<int, int>(3, 3) },
                { pair<int, int>(1, 1), pair<int, int>(3, 2), pair<int, int>(5, 3), pair<int, int>(4, 1), pair<int, int>(2, 3), pair<int, int>(1, 4) }
            } 
        };

        std::array<int, TEST_SIZE> expectResult { 
            { 
                3,
                4 
            } 
        };
};

// Tests member api insert
TEST_F(FindMaxNumOfPointsOnLineTestFixture, findMaxPointsOnLine) {

    std::array<int, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            return StaticApi::findMaxPointsOnLine(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}


/**
// Tests findImportantReversePairs()
class FindImportantReversePairsTestFixture : public ::testing::Test {
    public:

        FindImportantReversePairsTestFixture() = default;

        ~FindImportantReversePairsTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 2u;

        array<vector<int>, TEST_SIZE> inputTarget {
            { 
                { 1, 3, 2, 3, 1 },
                { 2, 4, 3, 5, 1 }
            } 
        };

        std::array<int, TEST_SIZE> expectResult { 
            { 
                2,
                3 
            } 
        };
};

// Tests member api insert
TEST_F(FindImportantReversePairsTestFixture, find) {

    std::array<int, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            cout << "test case" << endl;
            return StaticApi::findImportantReversePairs(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}
*/



// Tests SortByNumberLength()
class SortByNumberLengthTestFixture : public ::testing::Test {
    public:

        SortByNumberLengthTestFixture() = default;

        ~SortByNumberLengthTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 3u;

        array<vector<int>, TEST_SIZE> inputTarget {
            { 
                { 1, 54, 1, 2, 463, 2 },
                { 999, 421, 22, 990, 32 },
                { 9, 8, 7, 6, 5, 4, 31, 2, 1, 3 }
            } 
        };

        std::array<vector<int>, TEST_SIZE> expectResult { 
            { 
                { 1, 1, 2, 2, 54, 463 },
                { 22, 32, 999, 421, 990 },
                { 9, 8, 7, 6, 5, 4, 2, 1, 3, 31 }
            } 
        };
};

// Tests member api insert
TEST_F(SortByNumberLengthTestFixture, find) {

    std::array<vector<int>, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            return StaticApi::sortByNumberLengthMap(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

    std::array<vector<int>, TEST_SIZE> result1 = { };
    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result1.begin(),
        [] (const auto& entry) {
            return StaticApi::sortByNumberLengthList(entry);
        }
    );

    EXPECT_EQ(expectResult, result1);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}


// Tests SortByNumberLength()
class MaxAreaTestFixture : public ::testing::Test {
    public:

        MaxAreaTestFixture() = default;

        ~MaxAreaTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 4u;

        array<vector<uint>, TEST_SIZE> inputTarget {
            { 
                { 1, 8, 6, 2, 5, 4, 8, 3, 7 },
                { 1, 1 },
                { 4, 3, 2, 1, 4 },
                { 1, 2, 1 }
            } 
        };

        std::array<uint, TEST_SIZE> expectResult { 
            {
                49,
                1,
                16,
                2
            }
        };
};

// Tests member api insert
TEST_F(MaxAreaTestFixture, maxArea) {

    std::array<uint, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            return StaticApi::maxArea(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}


// Tests MergInterval()
class MergeIntervalTestFixture : public ::testing::Test {
    public:

        MergeIntervalTestFixture() = default;

        ~MergeIntervalTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 2u;

        array<vector<pair<uint, uint>>, TEST_SIZE> inputTarget {
            { 
                { {1, 3}, {2, 6}, {8, 10}, {15, 18} },
                { {1, 4}, {4, 5} }
            } 
        };

        std::array<vector<pair<uint, uint>>, TEST_SIZE> expectResult { 
            {
                { {1, 6}, {8, 10}, {15, 18} },
                { {1, 5} }
            }
        };
};

// Tests member api insert
TEST_F(MergeIntervalTestFixture, merge) {

    std::array<vector<pair<uint, uint>>, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            return StaticApi::merge(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}


// Tests IntToRoman
class IntToRomanTestFixture : public ::testing::Test {
    public:

        IntToRomanTestFixture() = default;

        ~IntToRomanTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 7u;

	    array<int, TEST_SIZE> inputTarget { { 0, 3, 4, 9, 58, 1994, 4000 } };

        std::array<std::string, TEST_SIZE> expectResult { 
            {
            "",
            "III",
            "IV",
            "IX",
            "LVIII",
            "MCMXCIV",
            ""
            }
        };
};

// Tests member api insert
TEST_F(IntToRomanTestFixture, convert) {

    std::array<std::string, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            return StaticApi::intToRomanUsingArray(entry);
        }
    );

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            return StaticApi::intToRomanUsingLambda(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests IntToWritten
class IntToWrittenTestFixture : public ::testing::Test {
    public:

        IntToWrittenTestFixture() = default;

        ~IntToWrittenTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 10u;

	    array<int, TEST_SIZE> inputTarget { { 0, 3, 14, 29, 508, 1994, 4000, 11111, 62345, -16 } };

        std::array<std::string, TEST_SIZE> expectResult { 
            {
            "zero",
            "three",
            "fourteen",
            "twenty nine",
            "five hundred and eight",
            "one thousand nine hundred ninety four",
            "four thousand",
            "eleven thousand one hundred eleven",
            "sixty two thousand three hundred forty five",
            "negative sixteen",
            }
        };
};

// Tests member api insert
TEST_F(IntToWrittenTestFixture, convert) {

    std::array<std::string, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) 
        {
            return StaticApi::intToWrittenUsingArray(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests restoreValidIPAddress
class RestoreValidIPAddressTestFixture : public ::testing::Test {
    public:

        RestoreValidIPAddressTestFixture() = default;

        ~RestoreValidIPAddressTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 6u;

	    array<std::string, TEST_SIZE> inputTarget { 
            { 
                "", 
                "0000",
                "1111",
                "010010",
                "101023",
                "000256"
            } 
        };

        std::array<std::vector<std::string>, TEST_SIZE> expectResult { 
            {
                { },
                { "0.0.0.0" },
                { "1.1.1.1" },
                { "0.100.1.0", "0.10.0.10" },
                { "101.0.2.3", "10.10.2.3", "10.1.0.23", "1.0.102.3", "1.0.10.23" },
                { },
            }
        };
};

// Tests member api insert
TEST_F(RestoreValidIPAddressTestFixture, convert) {

    std::array<std::vector<std::string>, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            return StaticApi::restoreValidIPAddress(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests sortList
class SortListTestFixture : public ::testing::Test {
    public:

        SortListTestFixture() = default;

        ~SortListTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 3u;

	    array<std::list<int>, TEST_SIZE> inputTarget { 
            { 
                { 4,2,1,3 }, 
                { -1,5,3,4,0 },
                { }
            } 
        };

        std::array<std::list<int>, TEST_SIZE> expectResult { 
            {
                { 1, 2, 3, 4},
                { -1, 0, 3, 4, 5 },
                { },
            }
        };
};

// Tests member api insert
TEST_F(SortListTestFixture, sort) {

    std::array<std::list<int>, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (auto entry) {
            StaticApi::sortList(entry);
            return entry;
        }
    );

    EXPECT_EQ(expectResult, result);
}

// Tests canJump
class CanJumpTestFixture : public ::testing::Test {
    public:

        CanJumpTestFixture() = default;

        ~CanJumpTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 6u;

	    array<std::vector<int>, TEST_SIZE> inputTarget { 
            { 
                { 1,3,1,1,4 }, 
                { 1,3,1,1,0 }, 
                { 0 },
                { -1 },
                { 3,2,1,0,4 },
                { }
            } 
        };

        std::array<bool, TEST_SIZE> expectResult { 
            {
                true,
                true,
                true,
                false,
                false,
                false
            }
        };
};

// Tests member api canJump
TEST_F(CanJumpTestFixture, canJump) {

    std::array<bool, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {
            return StaticApi::canJump(entry);
        }
    );

    EXPECT_EQ(expectResult, result);
}

// Tests removeduplicates
class RemoveDuplicatesTestFixture : public ::testing::Test {
    public:

        RemoveDuplicatesTestFixture() = default;

        ~RemoveDuplicatesTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 3u;

	    array<std::vector<int>, TEST_SIZE> inputTarget { 
            { 
                { }, 
                { 1,1,1,2,2,3 }, 
                { 0,0,1,1,1,1,2,3,3 } 
            } 
        };

        std::array<std::pair<size_t, std::vector<int>>, TEST_SIZE> expectResult { 
            {
                { 0, { } }, 
                { 5, { 1,1,2,2,3 } }, 
                { 7, { 0,0,1,1,2,3,3 } }
            }
        };
};

// Tests member api insert
TEST_F(RemoveDuplicatesTestFixture, remove) {

    array<pair<size_t, vector<int>>, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {

            // make a copy for in-place modification
            auto nums = entry;
            auto k = StaticApi::removeDuplicates(nums);
            return std::pair<size_t, std::vector<int>>( k, nums );
        }
    );

    EXPECT_EQ(expectResult, result);
}

// Tests numRescueBoats
class NumRescueBoatsTestFixture : public ::testing::Test {
    public:

        NumRescueBoatsTestFixture() = default;

        ~NumRescueBoatsTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 7u;

	    array<std::pair<std::vector<int>, size_t>, TEST_SIZE> inputTarget { 
            { 
                { { }, 0 }, 
                { { 1, 2 }, 0 }, 
                { { 1, 2 }, 5 * 10000 }, 
                { { 1, 2 }, 3 }, 
                { { 3, 2, 2, 1 }, 3 }, 
                { { 3, 2, 2, 1 }, 4 }, 
                { { 3, 5, 3, 4 }, 5 }, 
            } 
        };

        std::array<int, TEST_SIZE> expectResult { 
            {
                0, 
                -1, 
                -1, 
                1,
                3,
                2,
                4
            }
        };
};

// Tests member api numRescueBoats
TEST_F(NumRescueBoatsTestFixture, numRescueBoats) {

    array<int, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) {

            // make a copy for in-place modification
            auto people = entry.first;
            auto limit = entry.second;
            return StaticApi::numRescueBoats(people, limit);
        }
    );

    EXPECT_EQ(expectResult, result);
}

// Tests findMaxPickedFruits
class FindMaxPickedFruitsTestFixture : public ::testing::Test {
    public:

        FindMaxPickedFruitsTestFixture() = default;

        ~FindMaxPickedFruitsTestFixture() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 7u;

	    array<std::vector<uint>, TEST_SIZE> inputTarget { 
            { 
                { }, 
                { 1, 2, 1 }, 
                { 0, 1, 2, 2 }, 
                { 1, 2, 3, 2, 2 }, 
                { 1, 1, 1, 1, 1 }, 
                { 1, 1, 1, 2, 2, 2 }, 
                { 1, 2, 1, 2, 1, 2 }, 
            } 
        };

        std::array<uint, TEST_SIZE> expectResult { 
            {
                0, 
                3,
                3,
                4,
                5,
                6,
                6
            }
        };
};

// Tests member api numRescueBoats
TEST_F(FindMaxPickedFruitsTestFixture, findMaxPickedFruits) {

    array<uint, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) 
        {
            auto fruits = entry;
            return StaticApi::findMaxPickedFruits(fruits);
        }
    );

    EXPECT_EQ(expectResult, result);
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?

class LetterCombinations : public ::testing::Test {
    public:

        LetterCombinations() = default;

        ~LetterCombinations() = default;

        void SetUp() override {};

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 6u;

	    array<string, TEST_SIZE> inputTarget { { "", "12345", "1", "2", "7", "9" } };

        std::array<vector<string>, TEST_SIZE> expectResult { 
            {
                { },
                { },
                { },
                { "a", "b", "c" },
                { "p", "q", "r", "s" },
                { "w", "x", "y", "z" },
            }
        };
};

// Tests member api insert
TEST_F(LetterCombinations, convert) {

    std::array<vector<string>, TEST_SIZE> result = { };

    transform(inputTarget.cbegin(), inputTarget.cend(), 
        result.begin(),
        [] (const auto& entry) 
        {
            return StaticApi::letterCombinations(entry);
        }
    );

    EXPECT_EQ(expectResult, result);

  // <TechnicalDetails>
  //
  //   EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expect12ed value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case expect12_EQ is preferred.
  //
  // On the other hand, expect12_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}
