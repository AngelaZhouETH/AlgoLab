#include <iostream>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


void diet(int n, int m) {
	Program lp (CGAL::SMALLER, true, 0, false, 0);
	int l, u;
	for (int i = 0; i < n; i++) {
		cin >> l >> u;
		lp.set_b(2*i, -l);
		lp.set_b(2*i+1, u);
	}
	int p, c;
	for (int i = 0; i < m; i++) {
		cin >> p;
		lp.set_c(i, p);
		for (int j = 0; j < n; j++) {
			cin >> c;
			lp.set_a(i, 2*j, -c);
			lp.set_a(i, 2*j+1, c);
		}
	}
	Solution s = CGAL::solve_linear_program(lp, ET());
	if (s.is_optimal()) {
		cout << floor(CGAL::to_double(s.objective_value())) << endl;
	} else {
		if (s.is_infeasible()) {
			cout << "No such diet." << endl;
		} else {
			cout << "unbounded" << endl;
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	while (n != 0 && m != 0) {
		diet(n, m);
		cin >> n >> m;
	}
}