#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

void bistro(int n) {
	int x, y;
	vector<K::Point_2> pts(n);
	Triangulation t;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		pts[i] = K::Point_2(x, y);
	}
	t.insert(pts.begin(), pts.end());
	int m;
	cin >> m;
	K::Point_2 p;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		p = t.nearest_vertex(K::Point_2(x, y))->point();
		cout << setiosflags(ios::fixed) << setprecision(0) << pow((p.x() - x), 2) + pow((p.y() - y), 2) << endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	while (n > 0) {
		bistro(n);
		cin >> n;
	}
}