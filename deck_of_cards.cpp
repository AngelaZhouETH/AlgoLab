#include <iostream>
#include <cstdlib>

using namespace std;


void deck_of_cards() {
	int n, k;
	cin >> n;
	cin >> k;
	int x[n];
	for (int i = 0; i < n; i++) {
		cin >> x[i];
	}
	int s = 0, e = 0, val = x[0];
	int result_i = s, result_j = e, result_v = abs(val - k);
	while (result_v > 0) {
		if (val < k) {
			e++;
			if (e == n) break;
			val += x[e];
		} else if (val > k) {
			if (s < e) {
				s++;
				if (s == n) break;
				val -= x[s-1];
			} else {
				s++;
				e++;
				if (e == n) break;
				val = x[s];
			}
			
		}
		if (abs(val - k) < result_v) {
			result_i = s;
			result_j = e;
			result_v = abs(val - k);
		}
	}
	cout << result_i << ' ' << result_j << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		deck_of_cards();
	}
}