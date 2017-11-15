#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_edges_iterator  Edge_iterator;

using namespace std;

void graypes(int n) {
	int x, y;
	vector<K::Point_2> points(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		points[i] = K::Point_2(x, y);
	}
	Triangulation t;
	t.insert(points.begin(), points.end());
	
	// for (int i = 0; i < n; i++) {
	// 	cout << t.nearest_vertex(points[i])->point() << endl;
	// }

	double dx, dy, dist = -1;
	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
		dx = t.segment(e)[0][0] - t.segment(e)[1][0];
		dy = t.segment(e)[0][1] - t.segment(e)[1][1];
		if (dist == -1) dist = dx * dx + dy * dy;
		else dist = min(dist, dx * dx + dy * dy);
	}

	cout << ceil(sqrt(dist) / 2 * 100) << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	while (n > 0) {
		graypes(n);
		cin >> n;
	}
}