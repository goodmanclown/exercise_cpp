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
#include "BubbleSort.hxx"
#include "MdnEndpoint.hxx"
#include "gtest/gtest.h"


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


// Tests BubbleSort().

// Tests member api sort
TEST(BubbleSort, sort0) {

 	int inputElem[5] = { 10, 1, -1, -10, 100 };

	BubbleSort::sort(inputElem, 5);

	EXPECT_EQ(-10, inputElem[0]);

	EXPECT_EQ(-1, inputElem[1]);

	EXPECT_EQ(1, inputElem[2]);

	EXPECT_EQ(10, inputElem[3]);

	EXPECT_EQ(100, inputElem[4]);

	BubbleSort::sort(inputElem, 5, false);

	EXPECT_EQ(-10, inputElem[4]);

	EXPECT_EQ(-1, inputElem[3]);

	EXPECT_EQ(1, inputElem[2]);

	EXPECT_EQ(10, inputElem[1]);

	EXPECT_EQ(100, inputElem[0]);

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

// Tests member api sort
TEST(BubbleSort, sort1) {

	MdnEndpoint mep(4083330001U, 4083339999U);

	MdnEndpoint meprhs1(4083330000U, 4083330000U);

	MdnEndpoint meprhs2(4083340000U, 4083340000U);

	MdnEndpoint meprhs3(4083340001U, 4083349999U);

	MdnEndpoint meprhs4(4083350000U, 4083350000U);

 	MdnEndpoint inputElem[5] = { mep, meprhs1, meprhs2, meprhs3, meprhs4 };

	BubbleSort::sort(inputElem, 5);

	EXPECT_EQ(4083330000U, inputElem[0].mMin);

	EXPECT_EQ(4083330001U, inputElem[1].mMin);

	EXPECT_EQ(4083340000U, inputElem[2].mMin);

	EXPECT_EQ(4083340001U, inputElem[3].mMin);

	EXPECT_EQ(4083350000U, inputElem[4].mMin);

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

// Tests member api sort
TEST(BubbleSort, sort2) {

	MdnEndpoint mep(4083330001U, 4083339999U);

	MdnEndpoint meprhs1(4083330000U, 4083330000U);

	MdnEndpoint meprhs2(4083340000U, 4083340000U);

	MdnEndpoint meprhs3(4083340001U, 4083349999U);

	MdnEndpoint meprhs4(4083350000U, 4083350000U);

 	MdnEndpoint inputElem[5] = { meprhs1, mep, meprhs2, meprhs3, meprhs4 };

	BubbleSort::sort(inputElem, 5);

	EXPECT_EQ(4083330000U, inputElem[0].mMin);

	EXPECT_EQ(4083330001U, inputElem[1].mMin);

	EXPECT_EQ(4083340000U, inputElem[2].mMin);

	EXPECT_EQ(4083340001U, inputElem[3].mMin);

	EXPECT_EQ(4083350000U, inputElem[4].mMin);

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

// Tests member api sort
TEST(BubbleSort, sort3) {

	MdnEndpoint mep(4083330001U, 4083339999U);

	MdnEndpoint meprhs1(4083330000U, 4083330000U);

	MdnEndpoint meprhs2(4083340000U, 4083340000U);

	MdnEndpoint meprhs3(4083340001U, 4083349999U);

	MdnEndpoint meprhs4(4083350000U, 4083350000U);

 	MdnEndpoint inputElem[5] = { meprhs4, meprhs3, meprhs2, meprhs1, mep };

	BubbleSort::sort(inputElem, 5);

	EXPECT_EQ(4083330000U, inputElem[0].mMin);

	EXPECT_EQ(4083330001U, inputElem[1].mMin);

	EXPECT_EQ(4083340000U, inputElem[2].mMin);

	EXPECT_EQ(4083340001U, inputElem[3].mMin);

	EXPECT_EQ(4083350000U, inputElem[4].mMin);

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
