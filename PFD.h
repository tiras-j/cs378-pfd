#ifndef PFD_h
#define PFD_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <sstream>  // istringstream
#include <string>   // string
#include <vector>   // vector
#include <queue>    // priority_queue
#include <list>     // list

#define TASK_INDEX(A) ((A) - 1)

using namespace std;

typedef struct {
    int ID;
    int dep_count;
    list<int> succ;
} NODE;

typedef priority_queue<int, vector<int>, greater<int> > my_pq_t; 

// ---------
// PFD_print
// ---------
void PFD_print(ostream&, const vector<int>&);


vector<int> PFD_eval(vector<NODE>&, my_pq_t&);

// --------
// populate
// --------
void populate(istream&, vector<NODE>&, my_pq_t&);

// ---------
// PFD_solve
// ---------

void PFD_solve (istream&, ostream&);
#endif // PFD_h
