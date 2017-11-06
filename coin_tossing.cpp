#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;


// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge e, reverseE;
		bool success;
		tie(e, success) = add_edge(from, to, G);
		tie(reverseE, success) = add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[reverseE] = 0;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}
};



void coin_tossing() {
	int n, m;
	cin >> n >> m;
	int a, b, c;
	Graph G(n);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);
	Vertex src = add_vertex(G);
	Vertex sink = add_vertex(G);
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		if (c == 1) {
			eaG.addEdge(src, a, 1);
		} else if (c == 2) {
			eaG.addEdge(src, b, 1);
		} else if (c == 0) {
			Vertex new_v = add_vertex(G);
			eaG.addEdge(src, new_v, 1);
			eaG.addEdge(new_v, a, 1);
			eaG.addEdge(new_v, b, 1);
		}
	}
	int temp, sum_score = 0;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		eaG.addEdge(i, sink, temp);
		sum_score += temp;
	}
	if (sum_score == m && push_relabel_max_flow(G, src, sink) == m)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		coin_tossing();
	}
}