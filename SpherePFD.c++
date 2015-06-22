#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
#include <cassert>

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
void PFD_print(ostream& w, const vector<int>& order){
    for( auto i = order.begin(); i != order.end(); ++i){
        w << *i << " ";
    }
    w << endl;
}

// --------
// populate
// --------
void populate(istream& r, vector<NODE>& graph, my_pq_t& free_queue){
    // Initialize to zero to avoid issues with empty input.
    int size = 0, rules = 0, node = 0, dep = 0, count = 0, lcount = 0;
    string s;
    // Clear the first line
    r >> size >> rules;
    getline(r, s); // clean up the line
    assert(size >= 0);

    graph.resize(size);
    // We only iterate across the number of lines given by rules count
    // NOT until EOF, that is against spec. 
    while(lcount < rules){
        getline(r, s);
        istringstream sin(s);
        sin >> node >> count;
        graph[TASK_INDEX(node)].ID = node;
        graph[TASK_INDEX(node)].dep_count = count;
        while(sin >> dep){
            // Add node as a successor to each dep
            graph[TASK_INDEX(dep)].succ.push_back(node);
        }
        ++lcount;

    }

    assert(graph.size() == (unsigned int)size);

    // We have to run through once to setup free_list
    for(int i = 0; i < size; ++i){
        if(graph[i].ID == 0){
            // Vectors initialize elements via copy constructors
            // hence our structs will receieve recursive value initialization 
            // to zero. Nice!
            graph[i].ID = i+1;
            graph[i].dep_count = 0;
            free_queue.push(i+1);
        }
    }

}

// --------
// PFD_eval
// --------
vector<int> PFD_eval(vector<NODE>& graph, my_pq_t& free_queue){
    vector<int> order;

    while(!free_queue.empty()){
        int nextID = free_queue.top();
        free_queue.pop();
        order.push_back(nextID);
        for(int n : graph[TASK_INDEX(nextID)].succ){
            if(!--graph[TASK_INDEX(n)].dep_count){
                free_queue.push(n);
            }
        }
    }

    return order;
}   
// ---------
// PFD_solve
// ---------

void PFD_solve (istream& r, ostream& w) {
    vector<NODE> graph;
    my_pq_t free_queue;
    populate(r, graph, free_queue);
    vector<int> order = PFD_eval(graph, free_queue);
    PFD_print(w, order);
}

// ----
// main
// ----

int main() {
	PFD_solve (cin, cout);
	return 0;
}
