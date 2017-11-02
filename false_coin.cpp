#include <iostream>
#include <set>
#include <algorithm>

using namespace std;


void false_coin() {
	bool done = false;
	bool flag = false;
	int n, k;
	cin >> n;
	cin >> k;
	int temp;
	int cur_weight_num;
	char sign;
	set<int> less;
	set<int> greater;
	set<int> good;
	set<int> result;	
	for (int i = 0; i < k; i++) {
		cin >> cur_weight_num;
		set<int> left, right;
		for (int j = 0; j < cur_weight_num; j++) {
			cin >> temp;
			left.insert(temp);
		}
		for (int j = 0; j < cur_weight_num; j++) {
			cin >> temp;
			right.insert(temp);
		}
		cin >> sign;
		if (!done) {
			if (sign == '=') {
				good.insert(begin(left), end(left));
				good.insert(begin(right), end(right));
			} else if (sign == '<') {
				if(!flag) {
					less.insert(begin(left), end(left));
					greater.insert(begin(right), end(right));
					flag = true;
				} else {
					result.clear();
					set_intersection(begin(less), end(less), begin(left), end(left), inserter(result, begin(result)));
					less = result;
					result.clear();
					set_intersection(begin(greater), end(greater), begin(right), end(right), inserter(result, begin(result)));
					greater = result;
				}
			} else {
				if(!flag) {
					less.insert(begin(right), end(right));
					greater.insert(begin(left), end(left));
					flag = true;
				} else {
					result.clear();
					set_intersection(begin(less), end(less), begin(right), end(right), inserter(result, begin(result)));
					less = result;
					result.clear();
					set_intersection(begin(greater), end(greater), begin(left), end(left), inserter(result, begin(result)));
					greater = result;
				}
			}
			result.clear();
			set_difference(begin(less), end(less), begin(good), end(good), inserter(result, begin(result)));
			less = result;
			result.clear();
			set_difference(begin(greater), end(greater), begin(good), end(good), inserter(result, begin(result)));
			greater = result;
			// set<int>::iterator it;
			// for (it = begin(less); it != end(less); it++) {
			// 	cout << *it << " ";
			// }
			// cout << endl;
			// for (it = begin(greater); it != end(greater); it++) {
			// 	cout << *it << " ";
			// }
			// cout << endl;
			if(less.size() == 1 && greater.size() == 0) {
				// cout << "*******";
				cout << *less.begin() << endl;
				done = true;
			} else if(greater.size() == 1 && less.size() == 0 ) {
				// cout << "********";
				cout << *greater.begin() << endl;
				done = true;
			}
		}
	}
	if (!done) {
		int whole[n];
		for (int i = 0; i < n; i++) {
			whole[i] = i+1;
		}
		result.clear();
		set_difference(whole, whole+n, begin(good), end(good), inserter(result, begin(result)));
		if (result.size() == 1) {
			cout << *result.begin() << endl;
		} else {
			cout << 0 << endl;
		}
	}

}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		false_coin();
	}
}