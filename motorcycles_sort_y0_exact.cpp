#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;


struct ray {
	int idx;
	K::FT slope;
	long y0;
	bool operator < (const ray &ray_inst) const {
		return y0 > ray_inst.y0;
	}
};


void motorcycles() {
	int n;
	cin >> n;
	vector<ray> rays(n);
	long x1, y1;
	for (int i = 0; i < n; i++) {
		cin >> rays[i].y0 >> x1 >> y1;
		rays[i].idx = i;
		rays[i].slope = (K::FT)(y1-rays[i].y0)/(K::FT)x1;
	}
	sort(rays.begin(), rays.end());

	vector<int> result;
	vector< pair<ray*, int> > downs(n); // positive for slope
	int last_idx = -1;
	K::FT last_up_slope = -1, slope;
	int j;
	for (int i = 0; i < n; i++) {
		if (rays[i].slope >= 0) {
			if (last_idx > -1) { // downs previous
				for (j = last_idx; j >= 0; j--) {
					if (rays[i].slope > -downs[j].first->slope) { // same slope right side wins
						break;
					}
				}
				last_idx = j;
			}
			if (last_idx == -1) { // no downs
				if (last_up_slope == -1 || last_up_slope >= rays[i].slope) {
					result.push_back(rays[i].idx);
					last_up_slope = rays[i].slope;
				}
			}
		} else { // this ray is going down
			if (last_idx > -1) {
				for (j = last_idx; j >= 0; j--) {
					if (-rays[i].slope >= -downs[j].first->slope) {
						break;
					}
				}
				last_idx = j;
			}
			downs[++last_idx] = pair<ray*, int>(&rays[i], rays[i].idx);
		}
	}

	for (j = 0; j <= last_idx; j++) {
		result.push_back(downs[j].second);
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