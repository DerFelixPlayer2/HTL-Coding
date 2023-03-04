#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> ans;

void bfs(int root, vector<vector<int>> &adj, vector<int> &visited) {
	queue<int> q;
	q.push(root);

	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (visited[cur]) continue;
		visited[cur]++;
		for (int v: adj[cur]) {
			ans.push_back(v);
			q.push(v);
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> visited(n, 0);
	vector<vector<int>> conditions(n);

	for (int i = 0; i < m; i++) {
		int item, k;
		cin >> item >> k;
		for (int j = 0; j < k; j++) {
			int c;
			cin >> c;
			conditions[item - 1].push_back(c - 1);
			// conditions[c - 1].push_back(item - 1);
		}
	}

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			bfs(i, conditions, visited);
		}
	}

	for (auto v: ans) cout << v << " ";
	cout << endl;

	return 0;

}
