#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct MySum {
	vector<int> sum;
	int count;
	bool operator< (const MySum& MySum_inst) const {
		return sum < MySum_inst.sum || ((sum == MySum_inst.sum) && (count < MySum_inst.count));
	}
};

void lignt_museum() {
	int n, m;
	cin >> n >> m;
	vector<int> b(m);
	for (int i = 0; i < m; i++) {
		cin >> b[i];
	}
	vector< vector<int> > sw_on(n, vector<int>(m));
	vector< vector<int> > sw_off(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> sw_on[i][j];
			cin >> sw_off[i][j];
		}
	}
	int count = 0;
	int left_len = n/2, right_len = n - left_len;
	vector<MySum> left_sum(1<<left_len);
	vector<MySum> right_sum(1<<right_len);
	for (int s = 0; s < 1 << left_len; s++ ){ // iterate through all subsets
		count = 0;
		left_sum[s].sum = vector<int>(m, 0);
		for (int i = 0; i < left_len; ++i ){
			if( s & 1 << i ) {
				count++;
				for (int j = 0; j < m; j++) {
					left_sum[s].sum[j] += sw_off[i][j];
				}
			} else {
				for (int j = 0; j < m; j++) {
					left_sum[s].sum[j] += sw_on[i][j];
				}
			}
		}
		left_sum[s].count = count;
	}
	for (int s = 0; s < 1 << right_len; s++ ){ // iterate through all subsets
		count = 0;
		right_sum[s].sum = vector<int>(m, 0);
		for (int i = 0; i < right_len; ++i ){
			if( s & 1 << i ) {
				count++;
				for (int j = 0; j < m; j++) {
					right_sum[s].sum[j] += sw_off[i+left_len][j];
				}
			} else {
				for (int j = 0; j < m; j++) {
					right_sum[s].sum[j] += sw_on[i+left_len][j];
				}
			}
		}
		right_sum[s].count = count;
	}
	sort(left_sum.begin(), left_sum.end());
	sort(right_sum.begin(), right_sum.end());

	int result = n+1;
	bool flag;
	for (int i = 0, j = (1<<right_len)-1; i < 1<<left_len && j > -1;) {
		flag = true;
		for (int r = 0; r < m; r++) {
			if (left_sum[i].sum[r] + right_sum[j].sum[r] < b[r]) {
				i++;
				flag = false;
				break;
			} else if (left_sum[i].sum[r] + right_sum[j].sum[r] > b[r]) {
				j--;
				flag = false;
				break;
			} 
		}
		if (flag == true) {
			result = min(result, left_sum[i].count+right_sum[j].count);
			j--;
		}
	}

	if (result == n+1) {
		cout << "impossible\n";
	} else {
		cout << result << endl;
	}

}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		lignt_museum();
	}
}