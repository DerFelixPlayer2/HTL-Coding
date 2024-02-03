#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int bfs(vector<vector<int>> &adjacency_list, const int goal) {
	auto q = queue<pair<int, int>>();
	q.push({0, 0});
	auto visited = vector<bool>(goal + 1, false);

	while (!q.empty()) {
		auto node = q.front();
		q.pop();

		visited[node.first] = true;
		for (auto n : adjacency_list[node.first]) {
			if (!visited[n]) {
				if (n == goal) return node.second + 1;
				q.push({n, node.second + 1});
			}
		}
	}
	return -1;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> adjacency_list(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adjacency_list[u - 1].push_back(v - 1);
		adjacency_list[v - 1].push_back(u - 1);
	}

	cout << bfs(adjacency_list, n - 1) << endl;
}