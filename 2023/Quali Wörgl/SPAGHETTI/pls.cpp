#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
	int from, to, length, velocity;
	double time_to_cross;
	vector<int> visited_velocities;

	bool isVisited(int velocity) {
		if (this->velocity != 0) return visited_velocities.size() == 1;
		return find(visited_velocities.begin(), visited_velocities.end(),
					velocity) != visited_velocities.end();
	}

	void setVisited(int velocity) { visited_velocities.push_back(velocity); }

	double get_time_to_cross(int prev_velocity) {
		return this->velocity != 0 ? this->time_to_cross
								   : (double)this->length / prev_velocity;
	}
};

struct Node {
	int value, velocity_to_continue;
	double time_to_reach;
	vector<int> path;

	Node(int value, int velocity_to_continue, double time_to_reach,
		 const vector<int> &path) {
		this->value = value;
		this->velocity_to_continue = velocity_to_continue;
		this->time_to_reach = time_to_reach;
		for (auto e : path) this->path.push_back(e);
		this->path.push_back(value);
	}

	friend inline constexpr bool operator>(const Node &a, const Node &b) {
		return a.time_to_reach > b.time_to_reach;
	}
};

pair<double, vector<int>> dijkstra(vector<vector<Edge>> &adjacency_list,
								   const int n) {
	vector<double> times(n, 1e9);
	times[0] = 0;

	priority_queue<Node, vector<Node>, greater<Node>> q;
	q.push({0, 70, 0, vector<int>(0)});

	while (!q.empty()) {
		Node node = q.top();
		q.pop();

		if (node.value == n - 1) {
			return {times[n - 1], node.path};
		}

		for (Edge &edge : adjacency_list[node.value]) {
			if (edge.isVisited(node.velocity_to_continue)) continue;

			double time_to_cross =
				edge.get_time_to_cross(node.velocity_to_continue);
			if (times[edge.to] > node.time_to_reach + time_to_cross) {
				times[edge.to] = node.time_to_reach + time_to_cross;
			}

			edge.setVisited(node.velocity_to_continue);
			q.push(
				{edge.to,
				 edge.velocity != 0 ? edge.velocity : node.velocity_to_continue,
				 node.time_to_reach + time_to_cross, node.path});
		}
	}

	return {-1, vector<int>(0)};
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<Edge>> adjacency_list(n);
	for (int i = 0; i < m; i++) {
		int a, b, v, l;
		cin >> a >> b >> v >> l;
		adjacency_list[a].push_back({a, b, l, v, (double)l / v});
	}

	auto r = dijkstra(adjacency_list, n);

	cout << setprecision(15) << r.first << endl;
	for (int e : r.second) cout << e << " ";
	cout << endl;

	return 0;
}