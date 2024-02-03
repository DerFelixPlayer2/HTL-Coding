#include "cave.h"
#include <bits/stdc++.h>

using namespace std;

#define MAX 5001

int positions[MAX], connections[MAX];

void exploreCave(int N) {
	memset(positions, 0, sizeof(positions));
	memset(connections, -1, sizeof(connections));

	for (int i = 0; i < N; i++) {
		int r = tryCombination(positions);
		if (r == -1) {
			answer(positions, connections);
		}

	}


	answer(positions, connections);
}
