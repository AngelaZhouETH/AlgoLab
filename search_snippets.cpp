#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void search_snippets() {
	int n;
	cin >> n;
	int m[n];
	for (int i = 0; i < n; i++) {
		cin >> m[i];
	}
	vector< vector<int> > p(n);
	int temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m[i]; j++) {
			cin >> temp;
			p[i].push_back(temp);
		}
	}
	int result;
	vector<int> pointer(n, 0);
	vector<int> value(n);
	for (int i = 0; i < n; i++) {
		value[i] = p[i][0];
	}
	int max_value = * max_element(begin(value), end(value));
	vector<int>::iterator min_it = min_element(begin(value), end(value));
	result = max_value - *min_it;
	int min_idx = min_it - begin(value);
	int new_value;
	while(pointer[min_idx] < m[min_idx] - 1) {
		pointer[min_idx]++;
		if (pointer[min_idx] < m[min_idx] - 1 && p[min_idx][pointer[min_idx]+1] < max_value) continue;
		new_value = p[min_idx][pointer[min_idx]];
		value[min_idx] = new_value;
		if(new_value > max_value) {
			max_value = new_value;
		}
		min_it = min_element(begin(value), end(value));
		if (max_value - *min_it < result) result = max_value - *min_it;
		min_idx = min_it - begin(value);
	}
	cout << result + 1 << endl;

}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		search_snippets();
	}
}