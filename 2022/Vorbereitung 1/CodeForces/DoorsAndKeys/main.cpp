#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool canPass(const string& in) {
	int r = 0, g = 0, b = 0;
	for (char i: in) {
		switch (i) {
			case 'R':
				if (r == 0) return false;
				r--;
				break;
			case 'G':
				if (g == 0) return false;
				g--;
				break;
			case 'B':
				if (b == 0) return false;
				b--;
				break;
			case 'r':
				r++;
				break;
			case 'g':
				g++;
				break;
			case 'b':
				b++;
				break;
			default:
				return false;
		}
	}
	return true;
}

int main() {
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++) {
		string in;
		cin >> in;

		if (canPass(in)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}

}
