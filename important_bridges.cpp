#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace std;
using namespace boost;

namespace boost
{
  struct edge_component_t
  {
    enum
    { num = 555 };
    typedef edge_property_tag kind;
  } edge_component;
}

typedef adjacency_list<vecS, vecS, undirectedS,
	no_property, property <edge_component_t, int> 
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

	property_map < Graph, edge_component_t >::type component = get(edge_component, GT);
	int num_comps = biconnected_components(GT, component);

	vector< vector< pair<int, int> > > comp2edges(num_comps);

	EdgeIt ebeg, eend;
	for (tie(ebeg, eend) = edges(GT); ebeg != eend; ++ebeg) {
		comp2edges[component[*ebeg]].push_back(make_pair(source(*ebeg, GT), target(*ebeg, GT)));
	}

	vector< pair<int, int> > result;
	int s, t, temp;
	for (int i = 0; i < num_comps; i++) {
		if (comp2edges[i].size()==1) {
			s = comp2edges[i][0].first;
			t = comp2edges[i][0].second;
			if (s > t) {
				temp = s;
				s = t;
				t = temp;
			}
			result.push_back(make_pair(s, t));
		}
	}
	sort(result.begin(), result.end());

	cout << result.size() << endl;
	for (auto it=result.begin(); it != result.end(); it++) {
		cout << it->first << ' ' << it->second << endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		important_bridges();
	}
}