#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

double ceil_to_double(const K::FT& x) {
	double a = ceil(CGAL::to_double(x));
	while (a < x) a++;
	while (a >= x+1) a--;
	return a;
}

void antenna(int n) {
	double x, y;
	vector<K::Point_2> P(n);
	
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		P[i] = K::Point_2(x, y);
	}
	Min_circle mc(begin(P), end(P), true);
	Traits::Circle c = mc.circle();
	K::FT min_squared_r = c.squared_radius();

	int idx;
	for (auto it = mc.support_points_begin(); it != mc.support_points_end(); it++) {
		for (int i = 0; i < n; i++) {
			if (P[i] == *it) {
		  		P[i] = P[(i+1)%n];
				Min_circle temp_mc(begin(P), end(P), true);
				c = temp_mc.circle();
				if (c.squared_radius() < min_squared_r)
					min_squared_r = c.squared_radius();
				P[i] = *it;
				temp_mc.clear();
			}
		}
	}
	
	cout << setiosflags(ios::fixed) << setprecision(0) 
	<< ceil_to_double(sqrt(min_squared_r)) << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	while (n > 0) {
		antenna(n);
		cin >> n;
	}
}