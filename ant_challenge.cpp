#include <iostream>
#include <vector>
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


void ant_challenge() {
	int n, m, s, a, b;
	cin >> n >> m >> s >> a >> b;
	vector<Graph> GTs(s, Graph(n));
	vector<WeightMap> weightmaps(s);
	for (int i = 0; i < s; i++) {
		weightmaps[i] = get(edge_weight, GTs[i]);
	}
	int sp, ep, w;
	Edge e; bool success;
	for (int i = 0; i < m; i++) {
		cin >> sp >> ep;
		for (int j = 0; j< s; j++) {
			tie(e, success) = add_edge(sp, ep, GTs[j]);
			cin >> w;
			weightmaps[j][e] = w;
		}
	}

	int hive[s];
	for (int i = 0; i < s; i++) {
		cin >> hive[i];
	}

	vector<Vertex> predmap(n); // predecessor vector
	Vertex start;
	Graph GT_final(n);
	WeightMap weightmap_final = get(edge_weight, GT_final);
	for (int i = 0; i < s; i++) {
		start = hive[i];
		prim_minimum_spanning_tree(GTs[i], make_iterator_property_map(
			predmap.begin(), get(vertex_index, GTs[i])),
			root_vertex(start));
		for (int j = 0; j < n; ++j) {
			tie(e, success) = edge(j, predmap[j], GTs[i]);
			if (success) {
				int w_temp = weightmaps[i][e];
				tie(e, success) = add_edge(j, predmap[j], GT_final);
				weightmap_final[e] = w_temp;
			}
		}
	}

	vector<int> distmap(n); // We must use at least one of these
	dijkstra_shortest_paths(GT_final, a,
		predecessor_map(make_iterator_property_map( // named parameters
			predmap.begin(), get(vertex_index, GT_final))).
		distance_map(make_iterator_property_map( // concatenated by .
			distmap.begin(), get(vertex_index, GT_final))));
	
	cout << distmap[b] << endl;


}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		ant_challenge();
	}
}