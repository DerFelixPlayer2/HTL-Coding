#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

long long dijkstra(vector<vector<pair<int, int>>> &adjacency_list,
				   vector<pair<long, int>> &way, const int goal) {
	auto visited = vector<bool>(goal + 1, false);
	auto q = priority_queue<pair<long long, int>, vector<pair<long long, int>>,
							greater<pair<long long, int>>>();
	// weigth, node
	q.push({0, 0});

	while (!q.empty()) {
		auto node = q.top();
		q.pop();

		if (node.second == goal) {
			return node.first;
		}

		visited[node.second] = true;
		for (auto n : adjacency_list[node.second]) {
			if (!visited[n.second]) {
				if (way[n.second].first > node.first + n.first) {
					way[n.second] = {node.first + n.first, node.second};
				}

				q.push({node.first + n.first, n.second});
			}
		}
	}

	return -1;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> adjacency_list(n);
	vector<pair<long, int>> way(n, {__LONG_MAX__, -1});
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		adjacency_list[u - 1].push_back({w, v - 1});
		adjacency_list[v - 1].push_back({w, u - 1});
	}

	long long weigth = dijkstra(adjacency_list, way, n - 1);
	if (weigth == -1) {
		cout << -1 << endl;
	} else {
		cout << weigth << endl;
		vector<int> v;
		int next = n - 1;
		do {
			v.push_back(next + 1);
			next = way[next].second;
		} while (next != 0 && next != -1);
		cout << 1 << " ";
		for (int i = v.size() - 1; i >= 0; i--) {
			cout << v[i] << " ";
		}
		cout << endl;
	}
}

// 5 6 1 2 2 2 5 5 2 3 4 1 4 1 4 3 3 3 5 1