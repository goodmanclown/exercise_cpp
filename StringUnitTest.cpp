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

// #include <limits.h>
#include "String.hxx"
#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <array>

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


// Tests String().

// Tests member api find
TEST(StringUnitTest, find) {

	String mep("abcdefgh");

	EXPECT_TRUE(mep.find("def"));

	EXPECT_FALSE(mep.find("dfe"));

	EXPECT_FALSE(mep.find("deg"));

	EXPECT_TRUE(mep.find("gh"));

	EXPECT_FALSE(mep.find("ghi"));

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


// Tests member api indexOf
TEST(StringUnitTest, indexOf) {

	String mep("abcdefghdefgh");

	EXPECT_EQ(3, mep.indexOf("def"));

	EXPECT_EQ(-1, mep.indexOf("dfe"));

	EXPECT_EQ(-1, mep.indexOf("deg"));

	EXPECT_EQ(6, mep.indexOf("gh"));

	EXPECT_EQ(-1, mep.indexOf("ghi"));

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

// Tests member api lastIndexOf
TEST(StringUnitTest, lastIndexOf) {

	String mep("abcdefghdefgh");

	EXPECT_EQ(8, mep.lastIndexOf("def"));

	EXPECT_EQ(-1, mep.lastIndexOf("dfe"));

	EXPECT_EQ(-1, mep.lastIndexOf("deg"));

	EXPECT_EQ(11, mep.lastIndexOf("gh"));

	EXPECT_EQ(-1, mep.lastIndexOf("ghi"));

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

// Tests member api split
TEST(StringUnitTest, split) {

	String mep("abcd;;efgh;defgh");
	vector<String> output;
	uint32_t ret = mep.split(';', output);

	EXPECT_EQ(3, ret);
	EXPECT_EQ(String("abcd"), output[0]);
	EXPECT_EQ(String("efgh"), output[1]);
	EXPECT_EQ(String("defgh"), output[2]);

	String mep1("abcd");
	output.clear();
	ret = mep1.split(';', output);

	EXPECT_EQ(1, ret);
	EXPECT_EQ(String("abcd"), output[0]);

	String mep2(";;;;;");
	output.clear();
	ret = mep2.split(';', output);

	EXPECT_EQ(0, ret);
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


// Tests member api split
TEST(StringUnitTest, splitArray) {

	String mep("/abcd/;efgh;/defgh;12345");
	vector<String> output;
	uint32_t ret = mep.split(";/", output);

	EXPECT_EQ(4, ret);
	EXPECT_EQ(String("abcd"), output[0]);
	EXPECT_EQ(String("efgh"), output[1]);
	EXPECT_EQ(String("defgh"), output[2]);
	EXPECT_EQ(String("12345"), output[3]);

	String mep1("abcd");
	output.clear();
	ret = mep1.split(";/", output);

	EXPECT_EQ(1, ret);
	EXPECT_EQ(String("abcd"), output[0]);

	String mep2(";/;/;/;/;/;/");
	output.clear();
	ret = mep2.split(";/", output);

	EXPECT_EQ(0, ret);

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

// Tests member api split
TEST(StringUnitTest, splitWord) {

	String mep("applewood");

	string splitted;
	bool ret = mep.split(splitted);

	EXPECT_TRUE(ret);
	EXPECT_EQ("apple wood", splitted);

	splitted = "";

	String mep1("orange");
	ret = mep1.split(splitted);

	EXPECT_FALSE(ret);

	splitted = "";

	String mep2("   apple    wood   ");
	ret = mep2.split(splitted);

	EXPECT_TRUE(ret);
	EXPECT_EQ("apple wood", splitted);

	splitted = "";

	String mep3("   apple    orange");
	ret = mep3.split(splitted);

	EXPECT_TRUE(ret);
	EXPECT_EQ("apple orange", splitted);
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

// Tests member api shuffle
TEST(StringUnitTest, shuffle) {

	String mep("a");

	vector<string> output;
	output.clear();
	uint32_t ret = mep.shuffle(output);

	EXPECT_EQ(1, ret);

	String mep1("ab");

	output.clear();
	ret = mep1.shuffle(output);

	EXPECT_EQ(2, ret);
	
	cout << "input ab" << endl;
	cout << "output" << endl;
	for (uint32_t i=0; i<ret; i++) 
		cout << output[i] << endl;

	cout << "input " << mep1.data() << endl;

	String mep2("abc");

	output.clear();
	ret = mep2.shuffle(output);

	EXPECT_EQ(6, ret);

	cout << "input abc" << endl;
	cout << "output" << endl;
	for (uint32_t i=0; i<ret; i++) 
		cout << output[i] << endl;

	cout << "input " << mep2.data() << endl;

	String mep3("abcd");

	output.clear();
	ret = mep3.shuffle(output);

	EXPECT_EQ(24, ret);

	cout << "input abcd" << endl;
	cout << "output" << endl;
	for (uint32_t i=0; i<ret; i++) 
		cout << output[i] << endl;

	cout << "input " << mep3.data() << endl;

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

// Tests member api shuffleAndPrint
TEST(StringUnitTest, shuffleAndPrint) {

	String mep("a");

	mep.shuffleAndPrint();

	String mep1("ab");

	mep1.shuffleAndPrint();

	String mep2("abc");

	mep2.shuffleAndPrint();

	String mep3("abcd");

	mep3.shuffleAndPrint();

	String mep4("eabcd");

	mep4.shuffleAndPrint();

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

// Tests member api reverse
TEST(StringUnitTest, reverse) {

	String mep("a");
	mep.reverse();

	EXPECT_EQ(0, strcmp("a", mep.data()));

	String mep1("ab");
	mep1.reverse();

	EXPECT_EQ(0, strcmp("ba", mep1.data()));

	String mep2("abc");
	mep2.reverse();

	EXPECT_EQ(0, strcmp("cba", mep2.data()));

	String mep3("abcd");
	mep3.reverse();

	EXPECT_EQ(0, strcmp("dcba", mep3.data()));

	String mep4("abcde");
	mep4.reverse();

	EXPECT_EQ(0, strcmp("edcba", mep4.data()));


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

// Tests member api isEnough
TEST(StringUnitTest, isEnough) {

	String mep("");
	bool ret = mep.isEnough("note");

	EXPECT_FALSE(ret);

	String mep1("ab");
	ret = mep1.isEnough("");

	EXPECT_FALSE(ret);

	String mep2("abc");
	ret = mep2.isEnough("ab");

	EXPECT_TRUE(ret);

	String mep3("abcd");
	ret = mep3.isEnough("abcde");

	EXPECT_FALSE(ret);

	String mep4("aAbbcCeEddE");
	ret = mep4.isEnough("aabbccddeee");

	EXPECT_TRUE(ret);

	String mep5("aabbcceedde");
	ret = mep5.isEnough("aAbBcCddEEE");

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

// Tests member api countWord
TEST(StringUnitTest, countWord) {

    String mep;

	uint32_t ret = mep.countWord("note");

	EXPECT_EQ(ret, 0);

	ret = mep.countWord("wood");

	EXPECT_EQ(ret, 1);

	ret = mep.countWord("wwwwoodddd");

	EXPECT_EQ(ret, 1);

	ret = mep.countWord("wwoodddwwoodddd");

	EXPECT_EQ(ret, 2);

	ret = mep.countWord("wwoodddoowwoodddd");

	EXPECT_EQ(ret, 3);

	ret = mep.countWord("apple");

	EXPECT_EQ(ret, 1);

	ret = mep.countWord("applewood");

	EXPECT_EQ(ret, 2);

	ret = mep.countWord("doow");

	EXPECT_EQ(ret, 1);

	ret = mep.countWord("elppa");

	EXPECT_EQ(ret, 1);

	ret = mep.countWord("elppadoow");

	EXPECT_EQ(ret, 2);

	ret = mep.countWord("aaappleaappleapplewood");

	EXPECT_EQ(ret, 4);

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

// Tests member api countWord
TEST(StringUnitTest, countWordOnGrid) {

    char grid[5][5] = 
	{
		{'a', 'p', 'p', 'l', 'e'},
		{'p', 'p', 'p', 'l', 'e'},
		{'p', 'w', 'o', 'o', 'd'},
		{'l', 'w', 'o', 'o', 'd'},
		{'e', 'o', 'o', 'o', 0}
    };

	String mep;

	// go through each row
    uint32_t countWord = 0;

	// go through each row
    for (uint32_t rowIndex = 0; rowIndex < 5; rowIndex++) {
        string str;

        for (uint32_t colIndex = 0; colIndex < 5; colIndex++) {
			str += grid[rowIndex][colIndex];
		}

  		countWord += mep.countWord(str.c_str());
    }

	// go through each col
    for (uint32_t colIndex = 0; colIndex < 5; colIndex++) {
        string str;

   		for (uint32_t rowIndex = 0; rowIndex < 5; rowIndex++) {
			str += grid[rowIndex][colIndex];
		}

  		countWord += mep.countWord(str.c_str());
    }

    EXPECT_EQ(countWord, 4);

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

// Tests member api equalAlmost
TEST(StringUnitTest, equalAlmost) {

    {
		String mep("");
    	String mep1("");
		bool ret = mep.equalAlmost(mep1);

		EXPECT_FALSE(ret);
	}

    {
		String mep("a");
    	String mep1("ab");
		bool ret = mep.equalAlmost(mep1);

		EXPECT_TRUE(ret);
	}

    {
		String mep("esteem");
    	String mep1("steem");
		bool ret = mep.equalAlmost(mep1);

		EXPECT_TRUE(ret);
	}

    {
		String mep("steeem");
    	String mep1("steem");
		bool ret = mep.equalAlmost(mep1);

		EXPECT_TRUE(ret);
	}

    {
		String mep("steam");
    	String mep1("steem");
		bool ret = mep.equalAlmost(mep1);

		EXPECT_TRUE(ret);
	}

    {
		String mep("steae");
    	String mep1("steem");
		bool ret = mep.equalAlmost(mep1);

		EXPECT_FALSE(ret);
	}

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


// Tests member api isAllUnique
TEST(StringUnitTest, isAllUnique) {

    {
		String mep("abcdefgh");
		bool ret = mep.isAllUnique();

		EXPECT_TRUE(ret);
	}


    {
		String mep("aacdefgh");
		bool ret = mep.isAllUnique();

		EXPECT_FALSE(ret);
	}


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


// Tests member api removeDuplicate
TEST(StringUnitTest, removeDuplicate) {

    {
		String mep("abcdefgh");
		mep.removeDuplicate();

		EXPECT_EQ(strcmp(mep.data(), "abcdefgh"), 0);
	}


    {
		String mep("aacdefgh");
		mep.removeDuplicate();

		EXPECT_EQ(strcmp(mep.data(), "ahcdefg"), 0);
	}


    {
		String mep("abcaefah");
		mep.removeDuplicate();

		EXPECT_EQ(strcmp(mep.data(), "abchef"), 0);
	}

    {
		String mep("aaaaaaaaa");
		mep.removeDuplicate();

		EXPECT_EQ(strcmp(mep.data(), "a"), 0);
	}



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


// Tests member api removeDuplicate
TEST(StringUnitTest, countMaxBracketDepth) {

    {
		String mep("abcdefgh");
		auto ret = mep.countMaxBracketDepth();

		EXPECT_EQ(ret, 0);
	}


    {
		String mep("aac(defgh");
		auto ret = mep.countMaxBracketDepth();

		EXPECT_EQ(ret, 0);
	}


    {
		String mep("aac)defgh");
		auto ret = mep.countMaxBracketDepth();

		EXPECT_EQ(ret, 0);
	}

    {
		String mep("aac()defgh");
		auto ret = mep.countMaxBracketDepth();

		EXPECT_EQ(ret, 1);
	}


    {
		String mep("aac(de))fgh");
		auto ret = mep.countMaxBracketDepth();

		EXPECT_EQ(ret, 1);
	}

    {
		String mep("a(ac((de))f(g)h");
		auto ret = mep.countMaxBracketDepth();

		EXPECT_EQ(ret, 3);
	}
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

// Tests getKMostNGram()
class StringGetKMostNGram  : public ::testing::Test {
    public:

        StringGetKMostNGram() = default;

        ~StringGetKMostNGram() = default;

        void SetUp() override {

          vector<string> tmp;
          tmp.emplace_back("to match");
          expectResult[0] = tmp;

          tmp.clear();
          tmp.emplace_back("string to match");
          tmp.emplace_back("a string to");
          expectResult[1] = tmp;

          tmp.clear();
          tmp.emplace_back("to match for n");
          tmp.emplace_back("gram a string to");
          tmp.emplace_back("a string to match");
           expectResult[2] = tmp;
        };

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 3u;

        array<vector<string>, TEST_SIZE> expectResult = {};

        array<pair<size_t, size_t>, TEST_SIZE> inputTarget{ 
            { pair<size_t, size_t>(1, 2), 
              pair<size_t, size_t>(2, 3), 
              pair<size_t, size_t>(3, 4) 
            } 
        };

        const char* input = "This is a string to match for n gram a string to match";

        void GetExpect(const array<vector<string>, TEST_SIZE>& result)
        {
            EXPECT_EQ(result, expectResult);
        }
};

// Tests member api getKMostNGram
TEST_F(StringGetKMostNGram, getKMostNGram) {

    String str(input);

    auto index = 0u;
    array<vector<string>, TEST_SIZE> result = { };

    for ( auto& entry : inputTarget )
    {
        result[index++] = str.getKMostNGram(entry.first, entry.second);
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
