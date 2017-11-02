#include <iostream>
#include <limits>

using namespace std;


void dominoes() {
	int num;
	cin >> num;
	int result = 1, cur_height;
	for (int i = 1; i < num+1; i++) {
		if (result >= num) {
			result = num;
			break;
		}
		if (i > result) break;
		cin >> cur_height;
		if (i+cur_height-1 > result) result = i+cur_height-1;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << result << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		dominoes();
	}

}