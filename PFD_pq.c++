#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <list>
#include <queue>
#include <functional>

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
    int size, rules, node, dep, count;
    string s;
    // Clear the first line
    r >> size >> rules;
    getline(r, s); // clean up the line

    graph.resize(size);

    while(getline(r,s)){
        istringstream sin(s);
        sin >> node >> count;
        graph[TASK_INDEX(node)].ID = node;
        graph[TASK_INDEX(node)].dep_count = count;
        while(sin >> dep){
            // Add node as a successor to each dep
            graph[TASK_INDEX(dep)].succ.push_back(node);
        }

    }

    // We have to run through once to setup free_list
    for(int i = 0; i < size; ++i){
        if(graph[i].ID != i+1){
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
