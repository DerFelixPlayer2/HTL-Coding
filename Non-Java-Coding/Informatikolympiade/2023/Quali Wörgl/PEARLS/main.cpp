#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long llong;

struct Pearl {
	int amount, size, price;

	friend inline ostream &operator<<(ostream &stream, const Pearl &p) {
		return (stream << "{a=" << p.amount << " s=" << p.size
					   << " p=" << p.price << "}");
	}
};

void _perm(vector<Pearl> const &pearls, const int size, const int i,
		   vector<const Pearl *> &resulting,
		   vector<vector<const Pearl *>> &permutations) {
	if (i == size) {
		permutations.emplace_back(resulting);
	} else {
		for (int j = i; j < size; j++) {
			resulting.emplace_back(&pearls[j]);
			_perm(pearls, size, j + 1, resulting, permutations);
			resulting.pop_back();
		}
	}
}

void perm(vector<Pearl> &pearls, vector<vector<const Pearl *>> &permutations) {
	vector<const Pearl *> p;
	p.reserve(pearls.size());
	for (int i = 1; i <= pearls.size(); i++) {
		_perm(pearls, i, 0, p, permutations);
		p.clear();
	}
}

bool is_valid(map<int, llong, greater<int>> &map,
			  vector<const Pearl *> const &in,
			  vector<const Pearl *> const &out) {
	for (auto &v : in) {
		if (map.find(v->size) == map.end())
			map[v->size] = v->amount;
		else
			map[v->size] += v->amount;
	}
	for (auto &v : out) {
		if (map.find(v->size) == map.end())
			map[v->size] = -v->amount;
		else
			map[v->size] -= v->amount;
	}

	llong running_sum = 0;
	for (auto v : map) {
		running_sum += v.second;
		if (running_sum < 0) {
			return false;
		}
	}

	return true;
}

llong calc_profit(map<int, llong, greater<int>> &map,
				  vector<const Pearl *> const &in,
				  vector<const Pearl *> const &out) {
	if (!is_valid(map, in, out)) return INT32_MIN;

	llong pay = 0ll, receive = 0ll;
	for (auto v : in) pay += v->price;
	for (auto v : out) receive += v->price;
	return receive - pay;
}

llong bruteforce(vector<Pearl> &incoming, vector<Pearl> &outgoing) {
	llong sum = 0;

	map<int, llong, greater<int>> map;
	vector<vector<const Pearl *>> incoming_permutions;
	vector<vector<const Pearl *>> outgoing_permutions;
	incoming_permutions.reserve(pow(2, incoming.size() - 1));
	outgoing_permutions.reserve(pow(2, outgoing.size() - 1));

	perm(incoming, incoming_permutions);
	perm(outgoing, outgoing_permutions);

	for (auto &in_perm : incoming_permutions) {
		for (auto &out_perm : outgoing_permutions) {
			llong profit = calc_profit(map, in_perm, out_perm);
			if (profit > sum) {
				sum = profit;
			}
			map.clear();
		}
	}

	return sum;
}

int main() {
	int n, m;

	cin >> n;
	vector<Pearl> incoming(n);
	for (int i = 0; i < n; i++) {
		int p, s, v;
		cin >> p >> s >> v;
		incoming[i] = {p, s, v};
	}

	cin >> m;
	vector<Pearl> outgoing(m);
	for (int i = 0; i < m; i++) {
		int p, s, v;
		cin >> p >> s >> v;
		outgoing[i] = {p, s, v};
	}

	cout << bruteforce(incoming, outgoing) << endl;

	return 0;
}
