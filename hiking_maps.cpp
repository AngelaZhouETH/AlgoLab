#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// #include <algorithm>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;


using namespace std;

void hiking_maps() {
	int m, n;
	cin >> m >> n;
	vector<int> px(m), py(m);
	for (int i = 0; i < m; i++) {
		cin >> px[i] >> py[i];
	}
	vector< vector<int> > point_in_tri(m, vector<int>(n, 0));
	vector< vector<int> > leg_in_tri(m-1, vector<int>(n, 0));
	vector<K::Point_2> points(6);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> points[j];
		}
		for (int p = 0; p < m; p++) {
			bool success = true;
			for (int j = 0; j < 3; j++) {
				auto r = CGAL::orientation(points[2*j], points[2*j+1], K::Point_2(px[p], py[p]));
				if (r !=  CGAL::COLLINEAR && r != CGAL::orientation(points[2*j], points[2*j+1], points[(2*j+2)%6])) {
					success = false;
					break;
				}
			}
			if (success == true) {
				point_in_tri[p][i] = 1;
			}
			if (p > 0) {
				if (point_in_tri[p][i] == 1 && point_in_tri[p-1][i] == 1) {
					leg_in_tri[p-1][i] = 1;
				}
			}
		}
	}

	int result = n;
	vector<int> counter(m-1, 0);
	int num = 0;
	int front = 0, back = 0;
	while (true) {
		if (num < m-1) {
			if (back == n) break;
			back++;
			for (int i = 0; i < m-1; i++) {
				if (leg_in_tri[i][back-1] == 1)
					counter[i]++;
			}
		} else {
			result = min(result, back-front);
			front++;
			for (int i = 0; i < m-1; i++) {
				if (leg_in_tri[i][front-1] == 1)
					counter[i]--;
			}
		}
		num = 0;
		for (int i = 0; i < m-1; i++) {
			if (counter[i] > 0) num++;
		}
	}
	cout << result << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		hiking_maps();
	}
}