#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS,
	no_property,
	property<edge_weight_t, int>
	> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex; // Vertex type
typedef graph_traits<Graph>::edge_descriptor Edge; // Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; 
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void tracking() {
	int n, m, k, x, y;
	cin >> n >> m >> k >> x >> y;
	Graph GT(n*(k+1));
	WeightMap weightmap = get(edge_weight, GT);
	int sp, ep, w, d[m];
	Edge e; bool success;
	for (int i = 0; i < m; i++) {
		cin >> sp >> ep >> w >> d[i];
		if (d[i] == 0) {
			for (int j = 0; j < k+1; j++) {
				tie(e, success) = add_edge(sp+j*n, ep+j*n, GT);
				weightmap[e] = w;
			}
		} else {
			for (int j = 0; j < k; j++) {
				tie(e, success) = add_edge(sp+j*n, ep+(j+1)*n, GT);
				weightmap[e] = w;
				tie(e, success) = add_edge(ep+j*n, sp+(j+1)*n, GT);
				weightmap[e] = w;
			}
			tie(e, success) = add_edge(sp+k*n, ep+k*n, GT);
			weightmap[e] = w;
		}
	}

	vector<int> distmap(n*(k+1));
	vector<Vertex> predmap(n*(k+1));
	dijkstra_shortest_paths(GT, x,
		predecessor_map(make_iterator_property_map( // named parameters
			predmap.begin(), get(vertex_index, GT))).
		distance_map(make_iterator_property_map( // concatenated by .
			distmap.begin(), get(vertex_index, GT))));

	cout << distmap[y+k*n] << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		tracking();
	}
}