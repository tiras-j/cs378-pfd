#ifndef PFD_h
#define PFD_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>   // vector

using namespace std;

// ---------
// PFD_print
// ---------
void PFD_print(ostream& w, const vector<int>& order);

void print_graph(const vector<vector<int> >& graph);

vector<int> PFD_eval(vector<vector<int> >& graph);

// --------
// populate
// --------
void populate(istream& r, vector<vector<int> >& graph);

// ---------
// PFD_solve
// ---------

void PFD_solve (istream& r, ostream& w);
#endif // PFD_h
