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
#include "SingLinkedList.hxx"
#include "gtest/gtest.h"

#include <iostream>
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


// Tests SingLinkedList().

// Tests member api insert
TEST(SingLinkedListUnitTest, insert) {

	SingLinkedList tree;

	bool ret =  tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(4, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(9, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(7, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 5);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 8);
	EXPECT_FALSE(ret);
	cout << tree << endl;

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



// Tests member api insert
TEST(SingLinkedListUnitTest, remove) {

	SingLinkedList tree;

	bool ret =  tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(4, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(9, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(7, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 5);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.remove(5);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.remove(0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.remove(4);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.remove(2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.remove(3);
	EXPECT_FALSE(ret);
	cout << tree << endl;

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
TEST(SingLinkedListUnitTest, reverse) {

	SingLinkedList tree;

	bool ret =  tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(4, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(9, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(7, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 5);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 8);
	EXPECT_FALSE(ret);
	cout << tree << endl;

	tree.reverse();
	cout << tree << endl;
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



// Tests member api present
TEST(SingLinkedListUnitTest, present) {

	SingLinkedList tree;

	bool ret =  tree.insert(1, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(3, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(4, 3);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(5, 4);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(6, 5);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(7, 6);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(8, 7);
	EXPECT_TRUE(ret);
	cout << tree << endl;

	ret = tree.present(6);
	EXPECT_TRUE(ret);
	cout << tree << endl;

	ret = tree.present(9);
	EXPECT_FALSE(ret);
	cout << tree << endl;
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


// Tests member api copy
TEST(SingLinkedListUnitTest, copy) {

	SingLinkedList tree;

	bool ret =  tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(4, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(9, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(7, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 5);
	EXPECT_EQ(true, ret);
	cout << "tree " << tree << endl;

	SingLinkedList tree1(tree);
	cout << "tree1 " << tree1 << endl;

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


// Tests member api operator=
TEST(SingLinkedListUnitTest, assign) {

	SingLinkedList tree;

	bool ret =  tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(4, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(9, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(7, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 5);
	EXPECT_EQ(true, ret);
	cout << "tree " << tree << endl;

	SingLinkedList tree1;
	tree1 = tree;
	cout << "tree1 " << tree1 << endl;

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


// Tests member api operator==
TEST(SingLinkedListUnitTest, compare) {

	SingLinkedList tree;

	bool ret =  tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(4, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(9, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(7, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 5);
	EXPECT_EQ(true, ret);
	cout << "tree " << tree << endl;

	SingLinkedList tree1;
	tree1 = tree;
	cout << "tree1 " << tree1 << endl;

	EXPECT_TRUE(tree == tree1);

	ret = tree1.insert(10, 6);
	EXPECT_EQ(true, ret);
	cout << "tree1 " << tree1 << endl;

	EXPECT_FALSE(tree == tree1);

	ret = tree1.remove(7);
	EXPECT_EQ(true, ret);
	cout << "tree1 " << tree1 << endl;

	EXPECT_FALSE(tree == tree1);

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


// Tests member api middle
TEST(SingLinkedListUnitTest, middle) {

	SingLinkedList tree;

	SingLinkedListNodePtr mid = tree.middle();
	EXPECT_TRUE(mid == NULL);

	bool ret =  tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.middle();
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	ret = tree.insert(4, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.middle();
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	ret = tree.insert(9, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.middle();
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(4, mid->getValue());

	ret = tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.middle();
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	ret = tree.insert(7, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.middle();
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(2, mid->getValue());

	ret = tree.insert(2, 5);
	EXPECT_EQ(true, ret);
	cout << "tree " << tree << endl;

	mid = tree.middle();
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

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


// Tests member api last
TEST(SingLinkedListUnitTest, last) {

	SingLinkedList tree;

	SingLinkedListNodePtr mid = tree.last(0);
	EXPECT_TRUE(mid == NULL);

	bool ret =  tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.last(0);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	ret = tree.insert(4, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.last(1);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	mid = tree.last(0);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(4, mid->getValue());

	ret = tree.insert(9, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.last(2);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	mid = tree.last(1);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(4, mid->getValue());

	mid = tree.last(0);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(9, mid->getValue());

	ret = tree.insert(5, 0);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.last(2);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	ret = tree.insert(7, 1);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	ret = tree.insert(2, 2);
	EXPECT_EQ(true, ret);
	cout << tree << endl;

	mid = tree.last(2);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	ret = tree.insert(2, 5);
	EXPECT_EQ(true, ret);
	cout << "tree " << tree << endl;

	mid = tree.last(3);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(5, mid->getValue());

	mid = tree.last(1);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(2, mid->getValue());

	mid = tree.last(0);
	
	EXPECT_TRUE(mid != NULL);
	EXPECT_EQ(9, mid->getValue());

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


// Tests member api isPalindrome
TEST(SingLinkedListUnitTest, isPalindrome) {

	SingLinkedList tree;

	bool ret = tree.isPalinodrome();
	EXPECT_TRUE(ret);

	tree.insert(5, 0);
	cout << tree << endl;

	ret = tree.isPalinodrome();
	EXPECT_TRUE(ret);

	tree.insert(1, 0);
	cout << tree << endl;
	
	ret = tree.isPalinodrome();
	cout << tree << endl;
	EXPECT_FALSE(ret);

	tree.insert(5, 0);
	cout << tree << endl;
	
	ret = tree.isPalinodrome();
	cout << tree << endl;
	EXPECT_TRUE(ret);

	tree.insert(1, 0);
	cout << tree << endl;
	
	tree.insert(5, 0);
	cout << tree << endl;

	ret = tree.isPalinodrome();
	cout << tree << endl;
	EXPECT_TRUE(ret);

    tree.remove(0);
	cout << tree << endl;

    tree.remove(2);
	cout << tree << endl;

    tree.insert(1, tree.getLength());
	cout << tree << endl;

	ret = tree.isPalinodrome();
	cout << tree << endl;
	EXPECT_TRUE(ret);

	tree.insert(5, 0);
	cout << tree << endl;

	ret = tree.isPalinodrome();
	cout << tree << endl;
	EXPECT_FALSE(ret);

    tree.remove(4);
	cout << tree << endl;

	ret = tree.isPalinodrome();
	cout << tree << endl;
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


// Tests member api sortInto012
TEST(SingLinkedListUnitTest, sortInto012) {

	SingLinkedList expectedTree;
	expectedTree.insert(2,0);
	expectedTree.insert(2,0);
	expectedTree.insert(2,0);
	expectedTree.insert(1,0);
	expectedTree.insert(1,0);
	expectedTree.insert(0,0);
	expectedTree.insert(0,0);
	expectedTree.insert(0,0);

	SingLinkedList tree;
	tree.insert(2,0);
	tree.insert(0,0);
	tree.insert(2,0);
	tree.insert(1,0);
	tree.insert(0,0);
	tree.insert(1,0);
	tree.insert(0,0);
	tree.insert(2,0);

    tree.sortInto012();

	EXPECT_TRUE(tree == expectedTree);

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


// Tests member api sortInto012
TEST(SingLinkedListUnitTest, sortInto012No0) {

	SingLinkedList expectedTree;
	expectedTree.insert(2,0);
	expectedTree.insert(2,0);
	expectedTree.insert(2,0);
	expectedTree.insert(1,0);
	expectedTree.insert(1,0);
	expectedTree.insert(0,0);
	expectedTree.insert(0,0);
	expectedTree.insert(0,0);

	SingLinkedList tree;
	tree.insert(2,0);
	tree.insert(0,0);
	tree.insert(2,0);
	tree.insert(1,0);
	tree.insert(0,0);
	tree.insert(1,0);
	tree.insert(0,0);
	tree.insert(2,0);

    tree.sortInto012();

	EXPECT_TRUE(tree == expectedTree);

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


// Tests member api sortInto012
TEST(SingLinkedListUnitTest, sortInto012No1) {

	SingLinkedList expectedTree;
	expectedTree.insert(2,0);
	expectedTree.insert(2,0);
	expectedTree.insert(2,0);
	expectedTree.insert(0,0);
	expectedTree.insert(0,0);
	expectedTree.insert(0,0);

	SingLinkedList tree;
	tree.insert(2,0);
	tree.insert(0,0);
	tree.insert(2,0);
	tree.insert(0,0);
	tree.insert(0,0);
	tree.insert(2,0);

    tree.sortInto012();

	EXPECT_TRUE(tree == expectedTree);

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


// Tests member api sortInto012
TEST(SingLinkedListUnitTest, sortInto012No2) {

	SingLinkedList expectedTree;
	expectedTree.insert(1,0);
	expectedTree.insert(1,0);
	expectedTree.insert(0,0);
	expectedTree.insert(0,0);
	expectedTree.insert(0,0);

	SingLinkedList tree;
	tree.insert(0,0);
	tree.insert(1,0);
	tree.insert(0,0);
	tree.insert(1,0);
	tree.insert(0,0);

    tree.sortInto012();

	EXPECT_TRUE(tree == expectedTree);

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
