#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

using namespace std;
using namespace boost;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

typedef adjacency_list<vecS, vecS, directedS,
		no_property,
		no_property>					Graph;
typedef graph_traits<Graph>::vertex_descriptor		Vertex;	// Vertex type		
typedef graph_traits<Graph>::edge_descriptor		Edge;	// Edge type

bool ok(int n, int r, vector<K::Point_2>& pts, map<K::Point_2, int>& idx_map, int mid_idx) {
	Triangulation tri;
	Graph GT(n);
	tri.insert(pts.begin()+mid_idx, pts.end());
	int first, second;
	double dist;
	for (Edge_iterator e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e) {
		dist = sqrt(CGAL::to_double(CGAL::squared_distance(tri.segment(e).source(), tri.segment(e).target())));
		if (dist <= r) {
			first = idx_map[tri.segment(e).source()];
			second = idx_map[tri.segment(e).target()];
			add_edge(first, second, GT);
			add_edge(second, first, GT);
		}
	}
	vector<int> sccmap(n);	// Use this vector as exterior property map
	int nscc = strong_components(GT, 
			make_iterator_property_map(
				sccmap.begin(), get(vertex_index, GT)));
	vector<int> component_size(nscc, 0);
	for (int i = 0; i < n; i++) {
		component_size[sccmap[i]]++;
	}
	int max_size = 0;
	for (int i = 0; i < nscc; i++) {
		max_size = max(max_size, component_size[i]);
	}
	if (max_size >= mid_idx) {
		return true;
	} else {
		return false;
	}
}

void sith() {
	int n, r;
	cin >> n >> r;
	vector<K::Point_2> pts(n);
	map<K::Point_2, int> idx_map;
	for (int i = 0; i < n; i++) {
		cin >> pts[i];
		idx_map[pts[i]] = i;
	}

	int mid_idx;
	int start = 0, end = (n+1)/2;
	if (ok(n, r, pts, idx_map, end)) { 
		cout << end << endl;
		return;
	}

	while (end != start+1) {
		mid_idx = (start+end)/2;
		if (ok(n, r, pts, idx_map, mid_idx)) {
			start = mid_idx;
		} else {
			end = mid_idx;
		}
	}
	cout << start << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		sith();
	}
}