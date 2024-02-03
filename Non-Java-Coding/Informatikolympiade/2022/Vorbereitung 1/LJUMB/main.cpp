#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Gib eine einzige Zahl, maximale Anzahl an Murmeln die ein Kind bei optimaler Verteilung
// bekommt, aus.
int main() {
	int kids, marbleColors;
	cin >> kids >> marbleColors;

	vector<int> v(marbleColors);
	for (int i = 0; i < marbleColors; i++)
		cin >> v[i];

	// Sortiere die Murmeln nach der Anzahl der Murmeln, die ein Kind bekommt.
	sort(v.begin(), v.end());

	// Berechne die Anzahl der Murmeln, die ein Kind bekommt.
	int sum = 0;
	for (int i = 0; i < kids; i++)
		sum += v[i];
}
