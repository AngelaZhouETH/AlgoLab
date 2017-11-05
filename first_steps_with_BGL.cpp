#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
	no_property,
	property<edge_weight_t, int>
	> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex; // Vertex type
typedef graph_traits<Graph>::edge_descriptor Edge; // Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; 
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void first_steps_with_BGL() {
	int n, m;
	cin >> n >> m;
	Graph GT(n);
	WeightMap weightmap = get(edge_weight, GT);
	int sp, ep, w;
	for (int i = 0; i < m; i++) {
		cin >> sp >> ep >> w;
		Edge e; bool success;
		tie(e, success) = add_edge(sp, ep, GT);
		weightmap[e] = w;
	}

	vector<Vertex> predmap(n); // predecessor vector
	Vertex start = 0; // root vertex
	prim_minimum_spanning_tree(GT, make_iterator_property_map(
		predmap.begin(), get(vertex_index, GT)),
		root_vertex(start)); // optional
	int len_min_st = 0;
	for (int j = 0; j < n; ++j) {
		Edge e; bool success;
		tie(e, success) = edge(j, predmap[j], GT);
		if (success) {
			len_min_st += weightmap[e];
		}
	}

	vector<int> distmap(n); // We must use at least one of these
	dijkstra_shortest_paths(GT, 0,
		predecessor_map(make_iterator_property_map( // named parameters
			predmap.begin(), get(vertex_index, GT))).
		distance_map(make_iterator_property_map( // concatenated by .
			distmap.begin(), get(vertex_index, GT))));
	int d = 0;
	for (int u = 0; u < n; ++u) {
		if (distmap[u] > d) d = distmap[u];
	}

	cout << len_min_st << ' ' << d << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		first_steps_with_BGL();
	}
}