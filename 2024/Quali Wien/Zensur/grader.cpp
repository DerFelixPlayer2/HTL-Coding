#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>

#include "zensur.h"

using namespace std;

static string bad, hw, lw;
static int cnt, h = 0, l = 10000;

static void WA(const string &msg) {
	cerr << msg << "\n";
	exit(1);
}

bool sendMessage(const string &m) {
	cnt++;
	if (m.size() > 10000) {
		cerr << "Nachricht zu lang: " << m.size() << "\n";
		exit(1);
	}
	// cout << "MESSAGE:" << m << endl;
	for (char c : m)
		if (c < 'a' || c > 'z') WA("Nachricht enhaelt nicht nur a-z");
	for (int i = 0; i + 3 < m.size(); i++)
		if (equal(bad.begin(), bad.end(), m.begin() + i)) return true;
	return false;
}

int _main() {
	// cin >> bad;

	srand(time(nullptr));
	// ios_base::sync_with_stdio(false);

	// int d = 10000;
	// for (int i = 0; i < d; i++) {
	auto start = std::chrono::steady_clock::now();
	bad.clear();
	cnt = 0;
	/*for (int j = 0; j < 4; j++)
		bad += char('a' + rand() % 26);*/
	bad = "zzzz";

	// if (i % 400 == 0) printf("Still alive %.1f%\n", ((double) i / d) * 100);

	// printf("W: %s\n", bad.c_str());
	auto ans = findBannedWord();
	if (bad == ans) {
		// cout << "Ok, " << cnt << " Nachrichten\n";
		if (cnt > h) {
			h = cnt;
			hw = bad;
		} else if (cnt < l) {
			l = cnt;
			lw = bad;
		}
	} else
		cout << "Falsch, " << ans << " " << bad << "\n";

	auto end = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
			.count() > 1000) {
		cout << "Timed out: " << bad << "\n";
	}

	//}

	cout << "Highest: " << hw << " " << h << "\n";
	// cout << "Lowest: " << lw << " " << l << endl;

	return 0;
}

int main() {
	cin >> bad;
	auto ans = findBannedWord();
	if (bad == ans)
		cout << "Ok, " << cnt << " Nachrichten\n";
	else
		cout << "Falsch, " << ans << " " << bad << "\n";
	return 0;
}