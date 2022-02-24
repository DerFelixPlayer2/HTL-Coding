#include <bits/stdc++.h>

using namespace std;

queue<int> q;
vector<int> ans;

void bfs(int root, vector<vector<int>> &adj, vector<int> &visited) {
	q.empty();
	q.push(root);

	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (visited[cur]) continue;
		visited[cur]++;
		for (int v: adj[cur]) {
			//if (ans[v] == 0) {
			ans.push_back(v);
			q.push(v);
			//}
		}
	}
}

// Topological Sort
int main() {
	int n, m;
	cin >> n >> m;

	vector<int> visited(n + 1, 0);
	vector<vector<int>> adj(n + 1);
	vector<vector<int>> rev(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		rev[v].push_back(u);
	}

	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			bfs(i, adj, visited);
		}
	}

	for (int i = 0; i < n; i++) {
		cout << ans[i] << " ";
	}


	return 0;
}
