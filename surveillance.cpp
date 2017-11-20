#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	boost::property_map<Graph, boost::edge_capacity_t>::type		EdgeCapacityMap;
typedef	boost::property_map<Graph, boost::edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	boost::property_map<Graph, boost::edge_reverse_t>::type		ReverseEdgeMap;
typedef	boost::graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	boost::graph_traits<Graph>::edge_descriptor			Edge;
typedef	boost::graph_traits<Graph>::edge_iterator			EdgeIt;

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
		Edge e, rev_e;
		bool success;
		boost::tie(e, success) = boost::add_edge(from, to, G);
		boost::tie(rev_e, success) = boost::add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[rev_e] = 0; // reverse edge has no capacity!
		revedgemap[e] = rev_e;
		revedgemap[rev_e] = e;
	}
};

void surveillance() {
	int n, m, k, l;
	cin >> n >> m >> k >> l;
	vector<int> polices(k);
	vector<int> photographs(l);
	vector<int> from(m);
	vector<int> to(m);
	for (int i = 0; i < k; i++) {
		cin >> polices[i];
	}
	for (int i = 0; i < l; i++) {
		cin >> photographs[i];
	}
	for (int i = 0; i < m; i++) {
		cin >> from[i] >> to[i];
	}

	//flow1 from polices to photographs
	Graph G(2*n);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	int my_flow = min(k, l);
	for (int i = 0; i < m; i++) {
		eaG.addEdge(from[i], to[i], my_flow);
		eaG.addEdge(n+from[i], n+to[i], 1);
	}
	Vertex source = boost::add_vertex(G);
	Vertex target = boost::add_vertex(G);
	for (int i = 0; i < k; i++) {
		eaG.addEdge(source, polices[i], 1);
		eaG.addEdge(n+polices[i], target, 1);
	}
	vector<Edge> my_edges(l);
	for (int i = 0; i < l; i++) {
		eaG.addEdge(photographs[i], n+photographs[i], 1);
	}
	long flow = boost::push_relabel_max_flow(G, source, target);
	cout << flow << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		surveillance();
	}
}