#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct bomb {
	int idx;
	int time;
	bool operator< (const bomb& bomb_inst) const {
		return time < bomb_inst.time;
	}
};

void octopussy() {
	int n;
	cin >> n;

	int temp;
	vector<bomb> bombs(n);
	for (int i = 0; i < n; i++) {
		bombs[i].idx = i;
		cin >> temp;
		if (i > 0) {
			temp = min(temp, bombs[(i-1)/2].time-1);
		}
		bombs[i].time = temp;
	}
	sort(begin(bombs), end(bombs));
	
	int pai = 0;
	bool result = true;
	for (int i = 0; i < n; i++) {
		if (bombs[i].time > pai) {
			pai++;
		} else {
			result = false;
			break;
		}
	}
	if (result) {
		cout << "yes" << endl;
	} else {
		cout << "no" << endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		octopussy();
	}
}