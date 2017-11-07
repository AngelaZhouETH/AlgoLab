#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
		no_property,
		property<edge_weight_t, int>
		>					DistGraph;
typedef graph_traits<DistGraph>::vertex_descriptor		DistVertex;	// Vertex type		
typedef graph_traits<DistGraph>::edge_descriptor		DistEdge;	// Edge type
typedef graph_traits<DistGraph>::out_edge_iterator		OutEdgeIt;
typedef property_map<DistGraph, edge_weight_t>::type	WeightMap;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	FlowGraph;
typedef	property_map<FlowGraph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<FlowGraph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<FlowGraph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<FlowGraph>::edge_descriptor			FlowEdge;


class EdgeAdder {
	FlowGraph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	EdgeAdder(FlowGraph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	void addEdge(int from, int to, long capacity) {
		FlowEdge e, reverseE;
		bool success;
		tie(e, success) = add_edge(from, to, G);
		tie(reverseE, success) = add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[reverseE] = 0;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}
};


void marathon() {
	int n, m, s, f;
	cin >> n >> m >> s >> f;
	DistGraph G(n);
	WeightMap weightmap = get(edge_weight, G);
	int a, b, c, d;
	DistEdge e; bool success;
	vector< vector<int> > flow(n, vector<int>(n));
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c >> d;
		tie(e, success) = edge(a, b, G);
		if (success) {
			if (weightmap[e] > d) {
				weightmap[e] = d;
				flow[a][b] = c;
				flow[b][a] = c;
			} else if (weightmap[e] == d) {
				flow[a][b] += c;
				flow[b][a] += c;
			}
		} else {
			tie(e, success) = add_edge(a, b, G);
			weightmap[e] = d;
			flow[a][b] = c;
			flow[b][a] = c;
		}
	}
	vector<int> distmap(n);		// We must use at least one of these
	vector<DistVertex> predmap(n);	// vectors as an exterior property map.
	dijkstra_shortest_paths(G, s,
			predecessor_map(make_iterator_property_map(	// named parameters
					predmap.begin(), get(vertex_index, G))).
			distance_map(make_iterator_property_map(	// concatenated by .
					distmap.begin(), get(vertex_index, G))));	
	int p;
	FlowGraph G2(n);
	EdgeCapacityMap capacitymap = get(edge_capacity, G2);
	ReverseEdgeMap revedgemap = get(edge_reverse, G2);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G2);
	EdgeAdder eaG(G2, capacitymap, revedgemap);
	FlowEdge e2;

	vector<int> queue;
	queue.push_back(f);
	set<int> visited;
	OutEdgeIt oebeg, oeend;
	DistVertex v;
	while(!queue.empty()) {
		p = queue.back();
		queue.pop_back();
		if (visited.find(p) == visited.end()) {
			visited.insert(p);
			for (tie(oebeg, oeend) = out_edges(p, G); oebeg != oeend; ++oebeg) {
				v = target(*oebeg, G);
				if (distmap[v] + weightmap[*oebeg] == distmap[p]) {
					if (visited.find(v) == visited.end())
						queue.push_back(v);
					eaG.addEdge(v, p, flow[v][p]);
				}
			}
		}
	}

	cout << push_relabel_max_flow(G2, s, f) << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		marathon();
	}
}