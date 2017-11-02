#include <iostream>
#include <vector>

using namespace std;


void even_matrices() {
	int n;
	cin >> n;
	int x[n][n], s_row[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> x[i][j];
			if(j == 0) {
				s_row[i][j] = x[i][j];
			} else {
				s_row[i][j] = s_row[i][j-1] + x[i][j];
			}
		}
	}

	vector< vector< vector<int> > > evens(n, vector< vector<int> >(n, vector<int> (n, 0)));
	vector< vector< vector<int> > > odds(n, vector< vector<int> >(n, vector<int> (n, 0)));
	int sum_w;
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int w = 0; w <= j; w++) {
				if (w == j) {
					sum_w = s_row[i][j];
				} else {
					sum_w = s_row[i][j] - s_row[i][j-w-1];
				}
				if (i == 0) {
					if (sum_w % 2 == 0) {
						evens[i][j][w] = 1;
						odds[i][j][w] = 0;
					} else {
						evens[i][j][w] = 0;
						odds[i][j][w] = 1;
					}
				} else {
					if (sum_w % 2 == 0) {
						evens[i][j][w] = evens[i-1][j][w] + 1;
						odds[i][j][w] = odds[i-1][j][w];
					} else {
						evens[i][j][w] = odds[i-1][j][w];
						odds[i][j][w] = evens[i-1][j][w] + 1;
					}
				}
				count += evens[i][j][w];
			}
		}
	}
	cout << count << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		even_matrices();
	}
}