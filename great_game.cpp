#include <iostream>
#include <vector>
#include <map>

using namespace std;

int max_step(int start_pos, int n, vector< vector<int> >& tran, vector<int>& min_memo, vector<int>& max_memo);

int min_step(int start_pos, int n, vector< vector<int> >& tran, vector<int>& min_memo, vector<int>& max_memo) {
    if (start_pos == n-1) return 0;

    if (min_memo[start_pos] == -1) {
        int len = tran[start_pos].size();
        int result = n;
        for (int i = 0; i < len; i++) {
            result = min(result, max_step(tran[start_pos][i], n, tran, min_memo, max_memo)+1);
        }
        min_memo[start_pos] = result;
    }
    return min_memo[start_pos];
}

int max_step(int start_pos, int n, vector< vector<int> >& tran, vector<int>& min_memo, vector<int>& max_memo) {
    if (start_pos == n-1) return 0;

    if (max_memo[start_pos] == -1) {
        int len = tran[start_pos].size();
        int result = 0;
        for (int i = 0; i < len; i++) {
            result = max(result, min_step(tran[start_pos][i], n, tran, min_memo, max_memo)+1);
        }
        max_memo[start_pos] = result;
    }
    return max_memo[start_pos];
}

void great_game() {
    int n, m;
    cin >> n >> m;
    int start_r, start_b;
    cin >> start_r >> start_b;

    int u, v;
    vector< vector<int> > tran(n-1);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        tran[u-1].push_back(v-1);
    }

    vector<int> min_memo(n, -1);
    vector<int> max_memo(n, -1);
    int red = min_step(start_r-1, n, tran, min_memo, max_memo);
    int black = min_step(start_b-1, n, tran, min_memo, max_memo);
    if (red < black)
        cout << "0" << endl;
    else if (red > black)
        cout << "1" << endl;
    else if (red%2 == 0)
        cout << "1" << endl;
    else
        cout << "0" << endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    int testcase;
    cin >> testcase;
    for (int i = 0; i < testcase; i++) {
        great_game();
    }
}
