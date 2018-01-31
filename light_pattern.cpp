#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void light_pattern() {
	int n, k, x;
	cin >> n >> k >> x;
	vector<int> light(n);
	for (int i = 0; i < n; i++) {
		cin >> light[i];
	}
	int n_pattern = n/k;

	vector<int> v(n_pattern, 0);
	vector<int> f(n_pattern); // if flip this pattern
	vector<int> u(n_pattern); // if not flip this pattern
	for (int i = 0; i < n_pattern; i++) {
		for (int j = 0; j < k; j++) {
			if (((x & 1<<j) && light[(i+1)*k-1-j] == 0) || ((x & 1<<j) == 0 && light[(i+1)*k-1-j])) {
				v[i] += 1;
			}
		}
	}
	f[0] = k - v[0] + 1;
	u[0] = v[0];
	for (int i = 1; i < n_pattern; i++) {
		f[i] = min(k - v[i] + f[i-1], k - v[i] + u[i-1] + 2);
		u[i] = min(v[i] + u[i-1], v[i] + f[i-1]);
	}
	cout << min(f[n_pattern-1], u[n_pattern-1]) << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		light_pattern();
	}
}