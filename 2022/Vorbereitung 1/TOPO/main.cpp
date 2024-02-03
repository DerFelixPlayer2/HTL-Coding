#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> res;

void bfs(vector<vector<int>> &adjacency_list, queue<int> &queue, vector<int> &incoming) {
	while (!queue.empty()) {
		int node = queue.front();
		queue.pop();

		res.push_back(node + 1);
		//cout << (node + 1) << " ";
		for (int i: adjacency_list[node]) {
			incoming[i]--;

			if (incoming[i] == 0) {
				queue.push(i);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	res.reserve(n);
	vector<vector<int>> adjacency_list(n);
	vector<int> incoming(n, 0);
	for (int i = 0; i < m; i++) {
		int item, k;
		cin >> item >> k;

		for (int j = 0; j < k; j++) {
			int a;
			cin >> a;

			adjacency_list[a - 1].push_back(item - 1);
			incoming[item - 1]++;
		}
	}

	queue<int> q;
	for (int i = 0; i < n; i++) if (incoming[i] == 0) q.push(i);
	bfs(adjacency_list, q, incoming);
	for (auto v: incoming) {
		if (v != 0) {
			cout << -1 << endl;
			return 0;
		}
	}
	for (auto v: res) {
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
