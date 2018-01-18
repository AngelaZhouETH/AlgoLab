#include <iostream>
#include <climits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;	
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int n, m, q;
	cin >> n >> m >> q;
	Graph G(n);
	WeightMap weightmap = boost::get(boost::edge_weight, G);

	int lon, lat;
	for (int i = 0; i < n; i++) {
		cin >> lon >> lat;
	}
	int a, b, c;
	Edge e;	bool success;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		boost::tie(e, success) = boost::add_edge(a, b, G);
		weightmap[e] = c;
	}

	std::vector<Vertex> predmap(n);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	std::vector<int> distmap(n);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	
	int s, t;
	for (int i = 0; i < q; i++) {
		cin >> s >> t;
		boost::dijkstra_shortest_paths(G, s, // We MUST provide at least one of the two maps
		boost::predecessor_map(boost::make_iterator_property_map(predmap.begin(), boost::get(boost::vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(boost::make_iterator_property_map(distmap.begin(), boost::get(boost::vertex_index, G))));	// distance map as Named Parameter
		if (distmap[t] < INT_MAX) {
			cout << distmap[t] << endl;
		} else cout << "unreachable" << endl;
	}
}