#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void binary(vector<int>& path, pair<int, int>& q_item, vector<int>& result, vector<int>& ages) {
	if (ages[path[0]] <= q_item.second) {
		result[q_item.first] = path[0];
		return;
	}
	int left = 0;
	int right = path.size()-1;
	int middle;
	while (right > left+1) {
		middle = (left+right)/2;
		if (ages[path[middle]] <= q_item.second) {
			right = middle;
		} else {
			left = middle;
		}
	}
	result[q_item.first] = path[right];
}

void dfs(int v, vector<int>& path, vector< vector<int> >& tree, unordered_map< int, vector< pair<int, int> > >& query, vector<int>& result, vector<int>& ages) {
	path.push_back(v);
	for (int i = 0; i < query[v].size(); i++ ) {
		binary(path, query[v][i], result, ages);
	}

	for (int i = 0; i < tree[v].size(); i++) {
		dfs(tree[v][i], path, tree, query, result, ages);
	}
	path.pop_back();
}

void evolution() {
	int n, q;
	cin >> n >> q;

	vector<string> names(n);
	vector<int> ages(n);
	unordered_map<string, int> name2idx;
	for (int i = 0; i < n; i++) {
		cin >> names[i] >> ages[i];
		name2idx[names[i]] = i;
	}

	string name, name2;
	vector< vector<int> > children(n);
	for (int i = 0; i < n-1; i++) {
		cin >> name >> name2;
		children[name2idx[name2]].push_back(name2idx[name]);
	}

	int age;
	unordered_map< int, vector< pair<int, int> > > query;
	for (int i = 0; i < q; i++) {
		cin >> name >> age;
		query[name2idx[name]].push_back(pair<int, int>(i, age));
	}

	int root = max_element(ages.begin(), ages.end())-ages.begin();
	vector<int> result(q);
	vector<int> path;
	dfs(root, path, children, query, result, ages);

	for (int i = 0; i < q; i++) {
		cout << names[result[i]] << ' ';
	}
	cout << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		evolution();
	}
}