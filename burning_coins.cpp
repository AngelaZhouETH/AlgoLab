#include <iostream>
#include <vector>
#include <algorithm>
// #include <unordered_map>

using namespace std;

// int n;
// unordered_map<int, int> memo;

// int best_value(int start, int end, vector<int>& v) {
// 	if (start == end) return v[start];
// 	if (start + 1 == end) return max(v[start], v[end]);
// 	if (memo.find(start*n+end) == memo.end()) {
// 		int first = min(best_value(start+1, end-1, v), best_value(start, end-2, v)) + v[end];
// 		int second = min(best_value(start+1, end-1, v), best_value(start+2, end, v)) + v[start];
// 		memo[start*n+end] = max(first, second);
// 	}
// 	return memo[start*n+end];
// }

void burning_coins() {
	// memo.clear();
	int n;
	cin >> n;
	vector<int> v(n);
	int tmp;
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		v[i] = tmp;
	}

	vector< vector<int> > myDB(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		myDB[i][i] = v[i];
		if (i != n-1) myDB[i][i+1] = max(v[i], v[i+1]);
	}

	for (int i = 2; i < n ; i++) {
		for (int j = 0; j < n-i; j++) {
			int first = v[j] + min(myDB[j+1][j+i-1], myDB[j+2][j+i]);
			int second = v[j+i] + min(myDB[j][j+i-2], myDB[j+1][j+i-1]);
			myDB[j][j+i] = max(first, second);
		}
	}

	cout << myDB[0][n-1] << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		burning_coins();
	}
}