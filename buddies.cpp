#include <iostream>
// #include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;

using namespace std;
using namespace boost;

void buddies() {
	int n, c, f;
	cin >> n >> c >> f;
	std::unordered_map<string, int> name2idx;
	vector< vector<int> > charac(n, vector<int>(c));
	int idx_count = 0;
	string name;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c; j++) {
			cin >> name;
			if (name2idx.find(name) == name2idx.end()) {
				name2idx[name] = idx_count;
				idx_count++;
			}
			charac[i][j] = name2idx[name];
		}
		sort(charac[i].begin(), charac[i].end());
	}
	Graph G(n);
	vector<int> v_intersection;
	for (int i = 0; i < n-1; i++) {
		for (int j = i+1; j < n; j++) {
    		v_intersection.clear();
    		set_intersection(charac[i].begin(), charac[i].end(),
                          charac[j].begin(), charac[j].end(),
                          back_inserter(v_intersection));
    		if (v_intersection.size()>f) {
    			add_edge(i, j, G);
    		}
		}
	}

	vector<Vertex> matemap(n);		// We MUST use this vector as an Exterior Property Map: Vertex -> Mate in the matching
	edmonds_maximum_cardinality_matching(G, make_iterator_property_map(matemap.begin(), get(vertex_index, G)));
	int matchingsize = matching_size(G, boost::make_iterator_property_map(matemap.begin(), get(boost::vertex_index, G)));
	if (matchingsize * 2 == n) {
		cout << "not optimal" << endl;
	} else {
		cout << "optimal" << endl;
	}

}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		buddies();
	}
}