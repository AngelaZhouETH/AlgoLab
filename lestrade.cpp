#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Vertex_handle Vh;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void lestrade() {
	int z_target, u_target, v_target, w_target;
	cin >> z_target >> u_target >> v_target >> w_target;
	int a, g;
	cin >> a >> g;
	int x, y, u, v, w;
	vector< pair<K::Point_2, int> > pts(g);
	vector< vector<int> > info(g, vector<int>(3));
	for (int i = 0; i < g; i++) {
		cin >> x >> y >> u >> v >> w;
		pts[i].first = K::Point_2(x, y);
		info[i][0] = u;
		info[i][1] = v;
		info[i][2] = w;
		pts[i].second = i;
	}

	Triangulation tri;
	tri.insert(pts.begin(), pts.end());

	int z;
	Program lp(CGAL::LARGER, true, 0, true, 24);
	lp.set_b(0, u_target);
	lp.set_b(1, v_target);
	lp.set_b(2, w_target);
  	map<int, int> gang_map;
  	int idx;
	for (int i = 0; i < a; i++) {
		cin >> x >> y >> z;
		idx = tri.nearest_vertex(K::Point_2(x, y))->info();
		if (gang_map.find(idx) == gang_map.end()) {
			gang_map[idx] = z;
		} else {
			if (gang_map[idx] > z) {
				gang_map[idx] = z;
			}
		}
	}
	int count = 0;
	for (map<int, int>::iterator it = gang_map.begin(); it != gang_map.end(); it++) {
		lp.set_a(count, 0, info[it->first][0]);
		lp.set_a(count, 1, info[it->first][1]);
		lp.set_a(count, 2, info[it->first][2]);
		lp.set_c(count, it->second);
		count++;
	}

	// CGAL::Quadratic_program_options options;
	// options.set_pricing_strategy(CGAL::QP_BLAND);
	// Solution s = CGAL::solve_linear_program(lp, ET(), options);
	Solution s = CGAL::solve_linear_program(lp, ET());
	if (s.is_optimal() && s.objective_value() <= z_target) {
		cout << "L" << endl;
	} else {
		cout << "H" << endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		lestrade();
	}
}