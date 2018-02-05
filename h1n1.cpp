#include <iostream>
#include <vector>
#include <map>
#include <queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::All_faces_iterator  Face_iterator;
typedef Triangulation::Face_handle Face_handle;

using namespace std;


void h1n1(int n) {
	int x, y;
	vector<K::Point_2> pts(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		pts[i] = K::Point_2(x, y);
	}

	Triangulation tri;
	tri.insert(pts.begin(), pts.end());


	queue<Face_handle> q;
	for (Face_iterator f = tri.all_faces_begin(); f != tri.all_faces_end(); ++f) {
		if (tri.is_infinite(f)) {
			q.push(f);
		}
	}

	Face_handle f;
	K::Point_2 p1, p2;
	long dsquare;
	map<Face_handle, long> wide;
	while (!q.empty()) {
		f = q.front();
		q.pop();
		for (int i = 0; i < 3; i++) {
			if (!tri.is_infinite(f->neighbor(i))) {
				p1 = f->vertex((i+1)%3)->point();
				p2 = f->vertex((i+2)%3)->point();
				dsquare = (p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y());
				if (!tri.is_infinite(f)) dsquare = min(dsquare, wide[f]);
				if (wide.find(f->neighbor(i)) == wide.end() || wide[f->neighbor(i)] < dsquare) {
					wide[f->neighbor(i)] = dsquare;
					q.push(f->neighbor(i));
				}
			}
		}
	}

	int m;
	cin >> m;
	long d;
	Face_handle f2;
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> d;
		p1 = K::Point_2(x, y);
		p2 = tri.nearest_vertex(p1)->point();
		dsquare = (p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y());

		if (dsquare >= d ){
			f2 = tri.locate(p1);
			if (tri.is_infinite(f2) || wide[f2] >= 4*d)
				cout << 'y';
			else
				cout << 'n';
		} else {
			cout << 'n';
		}
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
