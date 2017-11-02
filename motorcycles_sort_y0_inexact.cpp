#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;


struct ray {
	int idx;
	double y0, x1, y1;
	bool operator < (const ray &ray_inst) const {
		return y0 > ray_inst.y0;
	}
};


void motorcycles() {
	int n;
	cin >> n;
	vector<ray> rays(n);
	for (int i = 0; i < n; i++) {
		cin >> rays[i].y0 >> rays[i].x1 >> rays[i].y1;
		rays[i].idx = i;
	}
	sort(rays.begin(), rays.end());

	vector<int> result;
	vector<ray> downs;
	ray last_up_ray;
	last_up_ray.idx = -1;
	vector<ray>::iterator it;

	for (int i = 0; i < n; i++) {
		if (rays[i].y1-rays[i].y0 >= 0) {
			if (!downs.empty()) { // downs previous
				for (it = downs.end()-1; it != downs.begin()-1; it--) {
					auto r = CGAL::compare_slopes(K::Line_2(K::Point_2(0, rays[i].y0), K::Point_2(rays[i].x1, rays[i].y1)), K::Line_2(K::Point_2(0, it->y0), K::Point_2((it->x1)*(-1), it->y1)));
					if (r == CGAL::LARGER) { // same slope right side wins
						break;
					}
				}
				downs.erase(it+1, downs.end());
			}
			if (downs.empty()) { // no downs
				if (last_up_ray.idx == -1 ) {
					result.push_back(rays[i].idx);
					last_up_ray = rays[i];
				} else {
					auto r = CGAL::compare_slopes(K::Line_2(K::Point_2(0, rays[i].y0), K::Point_2(rays[i].x1, rays[i].y1)), K::Line_2(K::Point_2(0, last_up_ray.y0), K::Point_2((last_up_ray.x1), last_up_ray.y1)));
					if (r != CGAL::LARGER) {
						result.push_back(rays[i].idx);
						last_up_ray = rays[i];
					}
				}
			}
		} else { // this ray is going down
			if (!downs.empty()) {
				for (it = downs.end()-1; it != downs.begin()-1; it--) {
					auto r = CGAL::compare_slopes(K::Line_2(K::Point_2(0, rays[i].y0), K::Point_2(rays[i].x1*(-1), rays[i].y1)), K::Line_2(K::Point_2(0, it->y0), K::Point_2((it->x1)*(-1), it->y1)));
					if (r != CGAL::SMALLER) {
						break;
					}
				}
				downs.erase(it+1, downs.end());
			}
			downs.push_back(rays[i]);
		}
	}

	for (it = downs.begin(); it != downs.end(); it++) {
		result.push_back(it->idx);
	}
	sort(result.begin(), result.end());
	for (vector<int>::iterator it = result.begin(); it != result.end(); it++) {
		cout << *it << ' ';
	}
	cout << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		motorcycles();
	}
}