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

void portfolios(int n, int m) {
	Program qp (CGAL::SMALLER, true, 0, false, 0);
	int c, r;
	for (int i = 0; i < n; i++) {
		cin >> c >> r;
		qp.set_a(i, 0, c);
		qp.set_a(i, 1, -r);
	}
	int v;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> v;
			if ( i >= j) {
				qp.set_d(i, j, 2*v);
			}
		}
	}
	for (int i = 0; i < m; i++) {
		cin >> c >> r >> v;
		qp.set_b(0, c);
		qp.set_b(1, -r);
		Solution s = CGAL::solve_quadratic_program(qp, ET());
		if (s.is_optimal()) {
			double currentV = CGAL::to_double(s.objective_value());
			if (currentV > v) {
				cout << "No." << endl;
			} else {
				cout << "Yes." << endl;
			}
		} else {
			cout << "No." << endl;
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	while (n != 0 && m != 0) {
		portfolios(n, m);
		cin >> n >> m;
	}
}