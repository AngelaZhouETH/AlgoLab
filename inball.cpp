#include <iostream>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void inball(int n) {
	Program lp (CGAL::SMALLER, false, 0, false, 0);
	int d, tmp, norm;
	cin >> d;
	const int R = d;
	for (int i = 0; i < n; i++) {
		norm = 0;
		for (int j = 0; j < d; j++) {
			cin >> tmp;
			lp.set_a(j, i, tmp);
			norm += tmp * tmp;
		}
		norm = sqrt(norm);
		lp.set_a(R, i, norm);
		cin >> tmp;
		lp.set_b(i, tmp);
	}
	lp.set_c(R, -1);
	lp.set_l(R, true, 0);
	Solution s = CGAL::solve_linear_program(lp, ET());
	if (s.is_optimal()) {
		cout << int(floor(-CGAL::to_double(s.objective_value()))) << endl;
	} else {
		if (s.is_infeasible()) {
			cout << "none" << endl;
		} else {
			cout << "inf" << endl;
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	while (n > 0) {
		inball(n);
		cin >> n;
	}
}