#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


void moving_books() {
	int n, m;
	cin >> n >> m;
	vector<int> strength(n);
	vector<int> weight(m);
	for (int i = 0; i < n; i++) {
		cin >> strength[i];
	}
	for (int i = 0; i < m; i++) {
		cin >> weight[i];
	}
	multiset< int, greater<int> > books(begin(weight), end(weight));

	sort(begin(strength), end(strength), greater<int>());

	if (strength[0] < *books.begin()) {
		cout << "impossible" << endl;
		return;
	}

	multiset<int>::iterator it;
	int rounds = 0;
	while (!books.empty()) {
		for (int i = 0; i < n; i++) {
			it = books.lower_bound(strength[i]);
			if (it != books.end()) {
				books.erase(it);
			} else break;
		}
		rounds++;
	}
	cout << 3*rounds-1 << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		moving_books();
	}
}