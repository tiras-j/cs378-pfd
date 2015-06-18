#include <vector>    // vector
#include <iostream>  // istream/ostream
#include <sstream>   // istringstream
#include <string>    // string
#include <algorithm> // sort
using namespace std;

// ---------
// PFD_print
// ---------
void PFD_print(ostream& w, const vector<int>& order){
	for( auto i = order.begin(); i != order.end(); ++i){
		w << *i << " ";
	}
}

void print_graph(const vector<vector<int> >& graph){
	cout << endl << endl;
	for(int i = 1; i < (int) graph.size(); ++i){
		for(int j = 1; j < (int) graph[i].size(); ++j){
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}
// --------
// PFD_eval
// --------
vector<int> PFD_eval(vector<vector<int> >& graph) {
	vector<int> order;
	vector<int> free_list;
	bool done = false;
	while(!done){
		done = true;
		for(int i = 1; i < (int) graph.size(); ++i){
			int acc = 0;
			for(int j = 1; j < (int) graph[i].size(); ++j){
				acc += graph[i][j]; // Counting outlinks
				//cout << "acc: " << acc << endl;
			}
			if(acc == 0 && graph[i][0] == 0){
				done = false;
				graph[i][0] = 1;
				free_list.push_back(i);
				// We can't clear here or we might mess
				// up the order later
			}
		}
		
		print_graph(graph);
		sort(free_list.begin(), free_list.end());
		// Now we need to clear the inlinks to each free_list node
		for(int col : free_list){
			for(int i = 1; i < (int) graph.size(); ++i){
				// walking down the column associated with the freed node.
				graph[i][col] = 0;
			}
			
			order.push_back(col);
		}
		free_list.clear();
		
		print_graph(graph);
	}
	return order;
}	
// --------
// populate
// --------
void populate(istream& r, vector<vector<int> >& graph){
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
	
	cout << "populate exit" << endl;
}

// ---------
// PFD_solve
// ---------

void PFD_solve (istream& r, ostream& w) {
	vector<vector<int> > adjacency_matrix;
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
	