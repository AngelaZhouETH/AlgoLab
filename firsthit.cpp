#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <algorithm>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

using namespace std;

double floor_to_double(const K::FT& x)
{
	double a = std::floor(CGAL::to_double(x));
	while (a > x) a -= 1;
	while (a+1 <= x) a += 1;
	return a;
}

void first_hit(int n) {
	double x, y, a, b;
	cin >> x >> y >> a >> b;
	K::Point_2 source(x, y), direction(a, b);
	K::Ray_2 ray(source, direction);
	double r, s, t, u;
	vector<K::Segment_2> segs(n);
	K::Point_2 result;
	K::Segment_2 ray_to_seg;
	bool is_changed = false;
	K::Segment_2 seg;
	for (int i = 0; i < n; i++) {
		cin >> r >> s >> t >> u;
		K::Point_2 p(r, s), q(t, u);
		seg = K::Segment_2(p, q);
		segs[i] = seg;
	}
	random_shuffle(begin(segs), end(segs));
	for (int i = 0; i < n; i++){
		seg = segs[i];
		if ((is_changed && CGAL::do_intersect(ray_to_seg, seg)) || (!is_changed && CGAL::do_intersect(ray, seg))) {
			auto o = CGAL::intersection(ray, seg);
			if (const K::Point_2* op = boost::get<K::Point_2>(&*o)) {
				result = *op;
				is_changed = true;
				ray_to_seg = K::Segment_2(source, result);
			} else if (const K::Segment_2* os = boost::get<K::Segment_2>(&*o)) {
				if(CGAL::collinear_are_ordered_along_line(source, os->source(), os->target()))
					result = os->source();
				else
					result = os->target();
				is_changed = true;
				ray_to_seg = K::Segment_2(source, result);
			}
			else // how could this be? -> error
				throw runtime_error("strange segment intersection");
		}
	}
	if (!is_changed)
		cout << "no\n";
	else
		cout << setiosflags(ios::fixed) << setprecision(0) << floor_to_double(result.x()) << ' ' << floor_to_double(result.y()) << "\n";
}

int main() {
	int n;
	cin >> n;
	while (n > 0) {
		first_hit(n);
		cin >> n;
	}
	return 0;
}