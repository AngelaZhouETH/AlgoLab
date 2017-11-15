#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_edges_iterator  Edge_iterator;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;


void germs(int n) {
	int l, b, r, t;
	cin >> l >> b >> r >> t;
	int x, y;
	vector<K::Point_2> pts(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		pts[i] = K::Point_2(x, y);
	}
	Triangulation tri;
	tri.insert(pts.begin(), pts.end());
	map<K::Point_2, double> dist;
	K::Point_2 p1, p2;
	double d;
	for (Vertex_iterator v = tri.finite_vertices_begin(); v != tri.finite_vertices_end(); ++v) {
		p1 = v->point();
		dist[p1] = min(min(p1.x()-l, r-p1.x()), min(p1.y()-b, t-p1.y()));
	}
	for (Edge_iterator e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e) {
		p1 = tri.segment(e)[0];
		p2 = tri.segment(e)[1];
		d = sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2))/2.0;
		if (dist[p1] > d)
			dist[p1] = d;
		if (dist[p2] > d)
			dist[p2] = d;
	}
	vector<double> result;
	for (Vertex_iterator v = tri.finite_vertices_begin(); v != tri.finite_vertices_end(); ++v) {
		p1 = v->point();
		result.push_back(dist[p1]);
	}
	sort(result.begin(), result.end());

	if (result[0] < 0.5)
		cout << 0 << ' ';
	else
		cout << ceil(sqrt(result[0]-0.5)) << ' ';
	if (result[n/2] < 0.5)
		cout << 0 << ' ';
	else
		cout << ceil(sqrt(result[n/2]-0.5)) << ' ';
	if (result[n-1] < 0.5)
		cout << 0 << endl;
	else
		cout << ceil(sqrt(result[n-1]-0.5)) << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	while (n > 0) {
		germs(n);
		cin >> n;
	}
}