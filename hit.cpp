#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

using namespace std;

void hit(int n) {
	double x, y, a, b;
	cin >> x >> y >> a >> b;
	K::Point_2 source(x, y), direction(a, b);
	K::Ray_2 ray(source, direction);

	bool done = false;
	double r, s, t, u;
	for (int i = 0; i < n; i++) {
		cin >> r >> s >> t >> u;
		if (!done) {
			K::Point_2 p(r, s), q(t, u);
			K::Segment_2 seg(p, q);
			if (CGAL::do_intersect(seg, ray)) {
				cout << "yes" << endl;
				done = true;
			}
		}
	}
	if (!done) cout << "no" << endl;
	return;
}

int main() {
	int n;
	cin >> n;
	while (n > 0) {
		hit(n);
		cin >> n;
	}
}