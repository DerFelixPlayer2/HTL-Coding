#include <bits/stdc++.h>

using namespace std;

bool a = false;

int dfs(int u, vector<vector<int>> &adj, vector<int> &visited, bool t) {
	if (visited[u]++) return -1;
	//visited[u]++;
	for (int v: adj[u]) {
		if (!visited[v]) {
			dfs(v, adj, visited, false);
		}
	}
	return u;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}


	vector<int> visited(n + 1, 0);
	int ans = 0, c = 0;
	for (int i = 0; i < n; i++) {
		int r = dfs(i + 1, adj, visited, true);
		if (r != -1) ans++;
		//else c++;
		//cout << r << "\n";
	}

	//cout << "\n" << c << "\n";
	cout << ans << endl;

	return 0;
}