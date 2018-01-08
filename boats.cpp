#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> len;
vector<int> pos;
vector<int> idx;

bool compare(int i, int j) {
	return pos[i] < pos[j];
}

void boats() {
	int n;
	cin >> n;
	len.reserve(n);
	pos.reserve(n);
	idx.reserve(n);
	int a, b;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		len.push_back(a);
		pos.push_back(b);
		idx.push_back(i);
	}


	sort(begin(idx), end(idx), compare);
	int start = pos[idx[0]];
	int start_idx = 1;
	int index, position, end = 0, next, end_temp;
	int count = 1;
	while(start_idx < n && end != -1) {
		end = -1;
		for(int j = start_idx; j < n; j++) {
			index = idx[j];
			position = pos[index];
			if (position < start) continue;
			if (end != -1 && end <= position) break;
			end_temp = start + len[index];
			if (position > end_temp) end_temp = position;
			if (end == -1) {
				end = end_temp;
				next = j;
			} else {
				if (end_temp < end) {
					end = end_temp;
					next = j;
				}
			}
		}
		if (end != -1) {
			start = end;
			start_idx = next + 1;
			count++;
		}
	}

	cout << count << endl;

	idx.clear();
	pos.clear();
	len.clear();
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		boats();
	}
}