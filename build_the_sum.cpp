#include <iostream>

using namespace std;


void do_sum() {
	int num;
	cin >> num;
	float sum = 0, tem;
	for (int i = 0; i < num; i++) {
		cin >> tem;
		sum += tem;
	}
	cout << sum << "\n";
}

int main() {
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		do_sum();
	}

}