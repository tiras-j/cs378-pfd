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
#include <cassert>  // assert

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
/**
 * Prints a vector to the output stream
 * @param w an ostream reference
 * @param order an int vector reference
 */
void PFD_print(ostream& w, const vector<int>& order);

// --------
// PFD_eval
// --------
/**
 * Evaluates the dependency graph using the priority queue to 
 * identify the next free node to add to the output order.
 * Process:
 *      Get top of PQ and add to output vec
 *      Walk through succ list of node and decrement dep_count
 *          if dep_count is zero add that node to PQ
 *      Continue until PQ is empty.
 * @param graph vector<NODE> reference
 * @param free_queue a my_pq_t reference (typedef priority_queue...)
 * @return vector of ints representing output
 */
vector<int> PFD_eval(vector<NODE>& graph, my_pq_t& free_queue);

// --------
// populate
// --------
/**
 * Populates the graph and priority queue with initial state 
 * based on the input file. Each NODE is indexed via it's TASKID
 * to allow constant time access to tasks, and each contains a list
 * of TASKIDs which depend on it, as well as the number of tasks it
 * depends on in NODE.dep_count. Priority queue contains all tasks which 
 * have no dependencies.
 * @param r an istream reference
 * @param graph a vector<NODE> reference to be populated.
 * @param free_queue a my_pq_t reference to be populated.
 */
void populate(istream& r, vector<NODE>& graph, my_pq_t& free_queue);

// ---------
// PFD_solve
// ---------
/**
 * Solves the dependency problem via populate and eval and prints solution.
 * @param r an istream reference, input file read from here
 * @param w an ostream reference, solution output here
 */
void PFD_solve (istream& r, ostream& w);
#endif // PFD_h
