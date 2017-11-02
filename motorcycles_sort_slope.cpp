#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;


struct ray {
	int idx;
	double y0;
	K::FT slope;
	bool operator < (const ray &ray_inst) const {
		if (slope != ray_inst.slope && slope != -ray_inst.slope)
			return abs(slope) < abs(ray_inst.slope);
		else if (slope != ray_inst.slope)
				return slope > ray_inst.slope;
		else {
			if (slope > 0) return y0 < ray_inst.y0;
			else return y0 > ray_inst.y0;
		}
	}
};


void motorcycles() {
	int n;
	cin >> n;
	double x1, y1;
	vector<ray> rays(n);
	for (int i = 0; i < n; i++) {
		cin >> rays[i].y0 >> x1 >> y1;
		rays[i].idx = i;
		rays[i].slope = (K::FT)(y1 - rays[i].y0)/x1;
	}
	sort(rays.begin(), rays.end());

	double up_y0_margin = rays[0].y0, down_y0_margin = rays[0].y0;
	vector<int> result;
	result.push_back(rays[0].idx);
	// cout << rays[0].idx << ' ' << rays[0].slope << ' ' << rays[0].y0 << endl;
	for (int i = 1; i < n; i++) {
		if (rays[i].slope >= 0 && rays[i].y0 > up_y0_margin) {
			// cout << rays[i].idx << ' ' << rays[i].slope << ' ' << rays[i].y0 << endl;
			result.push_back(rays[i].idx);
			up_y0_margin = rays[i].y0;
		} else if (rays[i].slope <= 0 && rays[i].y0 < down_y0_margin) {
			// cout << rays[i].idx << ' ' << rays[i].slope << ' ' << rays[i].y0 << endl;
			result.push_back(rays[i].idx);
			down_y0_margin = rays[i].y0;
		} else if (rays[i].slope >= 0 && rays[i].y0 < down_y0_margin) {
			down_y0_margin = rays[i].y0;
		} else if (rays[i].slope <= 0 && rays[i].y0 > up_y0_margin) {
			up_y0_margin = rays[i].y0;
		}
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