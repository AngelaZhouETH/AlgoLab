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

void kingdom_defence() {
	int l, p;
	cin >> l >> p;
	Graph G(l);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);
	Vertex src = add_vertex(G);
	Vertex sink = add_vertex(G);
	vector<int> source(l);
	int temp;
	int sum_flow = 0;
	for (int i = 0; i < l; i++) {
		cin >> source[i] >> temp;
		eaG.addEdge(i, sink, temp);
		sum_flow += temp;
	}
	int f, t, c, C;
	for (int i = 0; i < p; i++) {
		cin >> f >> t >> c >> C;
		source[f] -= c;
		source[t] += c;
		eaG.addEdge(f, t, C-c);
	}
	Edge e; bool success;
	for (int i = 0; i < l; i++) {
		if (source[i] >= 0)
			eaG.addEdge(src, i, source[i]);
		else {
			eaG.addEdge(i, src, 0);
			tie(e, success) = edge(i, sink, G);
			capacitymap[e] -= source[i];
			sum_flow -= source[i];
		}

	}
	if (push_relabel_max_flow(G, src, sink) == sum_flow)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		kingdom_defence();
	}
}