#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Face_handle Face_handle;

using namespace std;

map<Face_handle, int> is_visited;
bool dfs(Face_handle f, Triangulation& t, double d) {
	is_visited[f] = 1;
	if (t.is_infinite(f))
		return true;
	else {
		int x[3], y[3];
		for (int i = 0; i < 3; i++) {
			x[i] = f->vertex(i)->point().x();
			y[i] = f->vertex(i)->point().y();
		}
		for (int i = 0; i < 3; i++) {
			if (is_visited[f->neighbor(i)] != 1) {
				if (pow(x[(i+1)%3]-x[(i+2)%3], 2) + pow(y[(i+1)%3]-y[(i+2)%3], 2) >= 4*d) {
					if ( dfs(f->neighbor(i), t, d) ) return true;
				}
			}
		}
		return false;
	}
}

void h1n1(int n) {
	int x, y;
	vector<K::Point_2> pts(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		pts[i] = K::Point_2(x, y);
	}
	Triangulation t;
	t.insert(pts.begin(), pts.end());
	int m;
	cin >> m;
	double d;
	K::Point_2 new_p, p;
	Face_handle f;
	for (int i = 0; i < m; i++) {
		is_visited.clear();
		cin >> x >> y >> d;
		new_p = K::Point_2(x, y);
		p = t.nearest_vertex(new_p)->point();
		if (pow(x-p.x(), 2)+pow(y-p.y(), 2)<d) {
			cout << 'n';
			continue;
		}
		f = t.locate(new_p);
		if (dfs(f, t, d))
			cout << 'y';
		else
			cout << 'n';
	}
	cout << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	while (n > 0) {
		h1n1(n);
		cin >> n;
	}
}