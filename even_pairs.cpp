#include <iostream>

using namespace std;


void even_pairs() {
	int num;
	cin >> num;
	int sum[num];
	int even_count = 0;
	for (int i = 0; i < num; i++) {
		int x;
		cin >> x;
		if (i == 0) {
			sum[i] = x;
		} else {
			sum[i] = sum[i-1] + x;
		}
		if (sum[i] % 2 == 0) even_count++;
	}
	int odd_count = num - even_count;
	int result = even_count + even_count * (even_count - 1) / 2 + odd_count * (odd_count - 1) / 2;
	cout << result << "\n";
}

int main() {
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		even_pairs();
	}
}