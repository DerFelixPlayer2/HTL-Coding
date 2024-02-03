#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Item {
	int volumen, wert;

	Item(int v, int w) {
		this->volumen = v;
		this->wert = w;
	}
};

int rucksack(int maxVolumen, int n, const vector<Item> &items, vector<vector<int>> &memo) {
	if (n == 0 || maxVolumen == 0) {
		return 0;
	}

	if (memo[n][maxVolumen] != -1) {
		return memo[n][maxVolumen];
	}

	int res = 0;
	if (items[n - 1].volumen <= maxVolumen) {
		res = max(rucksack(maxVolumen - items[n - 1].volumen, n - 1, items, memo) + items[n - 1].wert,
				  rucksack(maxVolumen, n - 1, items, memo));
	} else {
		res = rucksack(maxVolumen, n - 1, items, memo);
	}

	memo[n][maxVolumen] = res;
	return res;
}

int main() {
	int n, maxVolume;
	vector<Item> items;

	cin >> maxVolume;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int volume, value;
		cin >> volume;
		cin >> value;
		items.emplace_back(volume, value);
	}

	vector<vector<int>> memo(n + 1, vector<int>(maxVolume + 1, -1));

	int result = rucksack(maxVolume, n, items, memo);
	cout << result << endl;

	/*vector<vector<int>> memo(n + 1, vector<int>(maxVolume + 1, -1));
	memo[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= maxVolume; j++) {
			if (j < items[i - 1].volumen) {
				memo[i][j] = memo[i - 1][j];
			} else {
				memo[i][j] = max(memo[i - 1][j], memo[i - 1][j - items[i - 1].volumen] + items[i - 1].wert);
			}
		}
	}

	int maxValue = 0;
	for (int i = 0; i <= maxVolume; i++) {
		if (memo[n][i] > maxValue) {
			maxValue = memo[n][i];
		}
	}
	cout << maxValue << endl;
	return 0;*/
}
