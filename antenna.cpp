#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

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
	K::Point_2 P[n];
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		P[i] = K::Point_2(x, y);
	}
	Min_circle  mc( P, P+n, true);
	Traits::Circle c = mc.circle();
	cout << setiosflags(ios::fixed) << setprecision(0)
	<< ceil_to_double(sqrt(c.squared_radius())) << endl;
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