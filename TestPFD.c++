// --------------------------------
// projects/PFD/TestPFD.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// eval
// ----

TEST(PFDFixture, eval_1) {
    ASSERT_EQ(1, 1);
}

// ----
// solve
// ----

TEST(PFDFixture, solve_1) {
	istringstream r("8 5\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n6 1 1\n");
	ostringstream w;
	PFD_solve(r, w);

	ASSERT_EQ("1 5 3 2 4 6 7 8 \n", w.str());

}

TEST(PFDFixture, solve_2) {
	istringstream r("2 0\n");
	ostringstream w;
	PFD_solve(r, w);

	ASSERT_EQ("1 2 \n", w.str());

}

TEST(PFDFixture, solve_3) {
	istringstream r("2 1\n1 1 2\n");
	ostringstream w;
	PFD_solve(r, w);

	ASSERT_EQ("2 1 \n", w.str());

}
