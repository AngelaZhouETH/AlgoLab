#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS
	// no_property,
	// property<edge_weight_t, int>
	> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex; // Vertex type
typedef graph_traits<Graph>::edge_descriptor Edge; // Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; 


void important_bridges() {
	int n, m;
	cin >> n >> m;
	Graph GT(n);
	Edge e; bool success;
	int sp, ep;
	for (int i = 0; i < m; i++) {
		cin >> sp >> ep;
		tie(e, success) = add_edge(sp, ep, GT);
	}
	vector<int> sccmap(n); // Use this vector as exterior property map
	int nscc = strong_components(GT, // Total number of components
		make_iterator_property_map(
		sccmap.begin(), get(vertex_index, GT)));
	cout << nscc << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		important_bridges();
	}
}