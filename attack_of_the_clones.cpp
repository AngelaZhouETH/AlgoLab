#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct jedi {
	int start;
	int end;
	bool normal;
	bool operator < (const jedi &jedi_inst) const {
		return end < jedi_inst.end;
	}
};

void attack() {
	int n, m;
	cin >> n >> m;
	vector<jedi> jedis(n);
	for (int i = 0; i < n; i++) {
		cin >> jedis[i].start >> jedis[i].end;
		jedis[i].normal = (jedis[i].end >= jedis[i].start);
	}

	sort(begin(jedis), end(jedis));

	int max_num = 0, num = 0;
	int bound, final;
	for (int start_idx = 0; start_idx < n; start_idx++) {
		num = 1;
		if (jedis[start_idx].normal) {
			bound = jedis[start_idx].end;
			for(int idx = 1; idx < n; idx++) {
				if (jedis[idx].start > bound && jedis[idx].normal) {
					num++;
					bound = jedis[idx].end;
				}
			}
			if (num > max_num) max_num = num;
			break;
		} else {
			bound = jedis[start_idx].end;
			final = jedis[start_idx].start;
			for (int idx = start_idx+1; idx < n; idx++) {
				if (jedis[idx].start > bound && jedis[idx].normal && jedis[idx].end < final) {
					num++;
					bound = jedis[idx].end;
				}
			}
			if (num > max_num) max_num = num;
		}
	}
	cout << max_num << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		attack();
	}
}