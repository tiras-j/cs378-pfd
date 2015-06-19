#include <vector>    // vector
#include <iostream>  // istream/ostream
#include <sstream>   // istringstream
#include <string>    // string
#include <algorithm> // sort
#include <cstdint>   // uint8_t
using namespace std;


// ---------
// PFD_print
// ---------
void PFD_print(ostream& w, const vector<int>& order){
	for( auto i = order.begin(); i != order.end(); ++i){
		w << *i << " ";
	}
    w << endl;
}

void print_graph(const vector<vector<uint8_t> >& graph){
	cout << endl << endl;
	for(int i = 1; i < (int) graph.size(); ++i){
		for(int j = 0; j < (int) graph[i].size(); ++j){
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}
// --------
// PFD_eval
// --------
vector<int> PFD_eval(vector<vector<uint8_t> >& graph) {
	vector<int> order;
	bool done = false;
	while(!done){
		done = true;
		for(int i = 1; i < (int) graph.size(); ++i){
			int acc = 0;
            // If already deleted jump to next row.
            if(graph[i][0])
                continue;
            // Check all outlinks
			for(int j = 1; j < (int) graph[i].size(); ++j){
				acc += graph[i][j];
			}
            // if no outlinks, we have no more dependency.
			if(acc == 0){
				done = false;
				graph[i][0] = 1;
                order.push_back(i);            
			    for(int x = 1; x < (int) graph.size(); ++x){
				    // walking down the column associated with the freed node.
				    graph[x][i] = 0;
		    	}
                break;
			}
		}
	    #ifdef DEBUG	
		    print_graph(graph);
        #endif
	}
	return order;
}	
// --------
// populate
// --------
void populate(istream& r, vector<vector<uint8_t> >& graph){
	string s;
	int node, num, dep, size, rules;
	
	r >> size >> rules;
	getline(r,s); // Clear the line.
	graph.resize(size + 1); // We'll use the ID as the index, hence 1 -> size + 1
	for(int i = 0; i < size + 1; ++i){ graph[i].resize(size + 1, 0); }
	
	while(getline(r, s)){
		istringstream sin(s);
		sin >> node >> num;
		while(sin >> dep){
			graph[node][dep] = 1;
		}	
	}
	
}

// ---------
// PFD_solve
// ---------

void PFD_solve (istream& r, ostream& w) {
	vector<vector<uint8_t> > adjacency_matrix;
	populate(r, adjacency_matrix);
	vector<int> order = PFD_eval(adjacency_matrix);
	PFD_print(w, order);
}

// ----
// main
// ----

int main() {
	PFD_solve (cin, cout);
	return 0;
}
	
