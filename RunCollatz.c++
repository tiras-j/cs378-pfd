// -------------------------------
// projects/PFD/RunPFD.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout

#include "PFD.h"

// ----
// main
// ----

int main () {
    using namespace std;
    PFD_solve(cin, cout);
    return 0;}
