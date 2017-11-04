#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

unordered_map<int, int> memo;
vector<int> m_multi_idx;
int n;

int hash_func(const vector<int>& v) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += m_multi_idx[i]*v[i];
    }
    return result;
}

int score(const vector<int>& state, const vector< vector<int> >& stack) {
    bool end_state = true;
    for (int i = 0; i < n; i++) {
        if (state[i] != 0) {
            end_state = false;
            break;
        }
    }
    if (end_state) return 0;

    if (memo.find(hash_func(state)) != memo.end()) return memo[hash_func(state)];
    int temp_score = 0;
    vector<int> selected_idx;
    vector<int> colors;
    for (int s = 1; s < 1<<n; s++) {
       selected_idx.clear();
       colors.clear();
        for (int i = 0; i < n; i++) {
            if (state[i] > 0) {
                if (s & 1<<i) {
                    colors.push_back(stack[i][state[i]-1]);
                    selected_idx.push_back(i);
                }
            }
        }
        if (!colors.empty()) {
            int sc = 0;
            if (colors.size() > 1) {
                sort(colors.begin(), colors.end());
                int count = 1;
                for (vector<int>::iterator it = colors.begin()+1; it != colors.end(); it++) {
                    if (*it == *(it-1)) count++;
                    else {
                        if (count > 1) {
                            sc += pow(2, count-2);
                        }
                        count = 1;
                    }
                }
                if (count > 1) sc += pow(2, count-2);
            }
            vector<int> new_state = state;
            for (vector<int>::iterator it = selected_idx.begin(); it != selected_idx.end(); it++) {
                new_state[*it]--;
            }
            temp_score = max(temp_score, sc+score(new_state, stack));
        }
    }
    memo[hash_func(state)] = temp_score;
    return memo[hash_func(state)];
}

void poker_chips() {
    m_multi_idx.clear();
    memo.clear();
    cin >> n;
    vector<int> m(n);
    m_multi_idx.reserve(n);
    for (int i = 0; i < n; i++) {
        cin >> m[i];
        if(i==0)
            m_multi_idx.push_back(1);
        else
            m_multi_idx.push_back(m_multi_idx[i-1]*(m[i-1]+1));
    }
    vector< vector<int> > stack(n, vector<int>());
    for (int i = 0; i < n; i++) {
        stack[i].reserve(m[i]);
        for (int j = 0; j < m[i]; j++) {
            int temp;
            cin >> temp;
            stack[i].push_back(temp);
        }
    }

    cout << score(m, stack) << endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int testcase;
    cin >> testcase;
    for (int i = 0; i < testcase; i++) {
        poker_chips();
    }
}
