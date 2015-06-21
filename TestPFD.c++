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
#include <algorithm> // mismatch

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
    vector<NODE> graph;
    my_pq_t free_q;
    istringstream r("8 5\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n6 1 1\n");
    populate(r, graph, free_q);
    vector<int> order = PFD_eval(graph, free_q);
    vector<int> test = {1, 5, 3, 2, 4, 6, 7, 8};

    for(auto i = test.begin(), j = order.begin(); i != test.end(); ++i, ++j){
        ASSERT_EQ(*i, *j);
    }
    ASSERT_EQ(8, order.size());
    
}

TEST(PFDFixture, eval_2) {
    vector<NODE> graph;
    my_pq_t free_q;
    istringstream r("2 1\n1 1 2\n");

    populate(r, graph, free_q);

    vector<int> order = PFD_eval(graph, free_q);
    vector<int> test = {2, 1};

    for(auto i = test.begin(), j = order.begin(); i != test.end(); ++i, ++j){
        ASSERT_EQ(*i, *j);
    }
    ASSERT_EQ(2, order.size());
}

TEST(PFDFixture, eval_3) {
    vector<NODE> graph;
    my_pq_t free_q;
    istringstream r("100 0\n");

    populate(r, graph, free_q);

    vector<int> order = PFD_eval(graph, free_q);
    int i = 1;
    for(auto j = order.begin(); j != order.end(); ++j){
        ASSERT_EQ(i, *j);
        ++i;
    }

    ASSERT_EQ(100, order.size());
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

// --------
// populate
// --------

TEST(PFDFixture, populate_1) {
	istringstream r("8 5\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n6 1 1\n");
    vector<NODE> graph;
    my_pq_t free_q;

    populate(r, graph, free_q);
    
    ASSERT_EQ(8, graph.size());
    ASSERT_EQ(3, free_q.size());
    ASSERT_EQ(1, free_q.top());
}

TEST(PFDFixture, populate_2) {
    istringstream r("2 1\n1 1 2\n");
    vector<NODE> graph;
    my_pq_t free_q;

    populate(r, graph, free_q);

    ASSERT_EQ(2, graph.size());
    ASSERT_EQ(2, free_q.top());
}

TEST(PFDFixture, populate_3) {
    istringstream r("100 0\n");
    vector<NODE> graph;
    my_pq_t free_q;

    populate(r, graph, free_q);

    ASSERT_EQ(100, graph.size());
    ASSERT_EQ(100, free_q.size());
    ASSERT_EQ(1, free_q.top());
}

// ---------
// PFD_print
// ---------

TEST(PFDFixture, print_1){
    vector<int> test = {1, 2, 3, 4, 5, 6};
    ostringstream w;

    PFD_print(w, test);
    ASSERT_EQ("1 2 3 4 5 6 \n", w.str());
}

TEST(PFDFixture, print_2){
    vector<int> test = {1, 2};
    ostringstream w;
    PFD_print(w, test);
    ASSERT_EQ("1 2 \n", w.str());
}

TEST(PFDFixture, print_3){
    vector<int> test = {};
    ostringstream w;
    PFD_print(w, test);
    ASSERT_EQ("\n", w.str());
}
