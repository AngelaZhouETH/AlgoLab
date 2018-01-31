#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


void n_and_q() {
	int k, n, q;
	cin >> k >> n >> q;
	int lb, ub;
	vector<int> dim(k);
	for (int i = 0; i < k; i++) {
		cin >> lb >> ub;
		dim[i] = ub-lb+1;
	}
	vector<int> DB_arg(k);
	DB_arg[k-1] = 1; //The last one
	for (int i = k-2; i >=0; i--) {
		DB_arg[i] = DB_arg[i+1] * dim[i+1];
	}
	unordered_map<int, int> myDB;
	int tmp;
	int arg;
	for (int i = 0; i < n; i++) {
		arg = 0;
		for (int j = 0; j < k; j++) {
			cin >> tmp;
			arg += tmp * DB_arg[j];
		}
		cin >> tmp;
		myDB[arg] = tmp;
	}

	for (int i = 0; i < q; i++) {
		arg = 0;
		for (int j = 0; j < k; j++) {
			cin >> tmp;
			arg += tmp * DB_arg[j];
		}
		if (myDB.find(arg) != myDB.end()) {
			cout << myDB[arg] << endl;
		} else {
			cout << -1 << endl;
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		n_and_q();
	}
}