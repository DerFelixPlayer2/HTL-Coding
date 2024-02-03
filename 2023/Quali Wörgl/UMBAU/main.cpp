#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

typedef long long llong;

using namespace std;

struct Edge {
	llong from, to, weigth, index;

	friend inline constexpr bool operator<(const Edge &a, const Edge &b) {
		return a.weigth < b.weigth;
	}
};

pair<llong, vector<Edge *> *> mst(vector<Edge> &edges, const llong n) {
	priority_queue<Edge> q;
	q.push({-1, 0, 0, -1});
	vector<bool> visited(n, false);
	static vector<Edge *> mst_edges;
	llong mst_weight = 0;

	while (!q.empty()) {
		auto e = q.top();
		q.pop();

		if (visited[e.to]) continue;
		visited[e.to] = true;

		if (e.from != -1) {
			mst_edges.push_back(&edges[e.index]);
			mst_weight += e.weigth;
		}	

		for (auto &e : edges) {
			if (e.from == e.to) continue;
			if (visited[e.from] && visited[e.to]) continue;
			if (visited[e.from] || visited[e.to]) q.push(e);
		}
	}

	return {mst_weight, &mst_edges};
}

int main() {
	llong n, m;
	cin >> n >> m;

	// vector<vector<Edge>> adjacency_list(n);
	vector<Edge> edges(m);
	vector<llong> weights(m);
	for (llong i = 0; i < m; i++) {
		llong a, b, c;
		cin >> a >> b >> c;

		// adjacency_list[a - 1].push_back({a - 1, b - 1, c, i});
		// adjacency_list[b - 1].push_back({b - 1, a - 1, c, i});
		edges[i] = {a - 1, b - 1, c, i};
		weights[i] = c;
	}

	vector<llong> current_active(n - 1);
	for (llong i = 0; i < n - 1; i++) {
		llong c;
		cin >> c;
		current_active[i] = c - 1;
	}

	auto r = mst(edges, n);
	// for (auto e : mst.second) cout << e.from + 1 << " -> " << e.to + 1 <<
	// endl;
	llong sum = 0;
	for (llong i = 0; i < n - 1; i++) sum += weights[current_active[i]];
	cout << (sum - r.first) << endl;

	return 0;
}