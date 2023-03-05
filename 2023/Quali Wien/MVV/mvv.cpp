#include "mvv.h"
#include <cmath>

using namespace std;

char getC(char c1, char c2) {
	if (c1 == c2) return c1;
	if ((c1 == 'R' || c2 == 'R') && (c1 == 'B' || c2 == 'B')) return 'G';
	if ((c1 == 'R' || c2 == 'R') && (c1 == 'G' || c2 == 'G')) return 'B';
	if ((c1 == 'G' || c2 == 'G') && (c1 == 'B' || c2 == 'B')) return 'R';
	exit(-1);
}

int getInc(size_t size, size_t i) {
	for (int j = 15; j >= 0; j--)
		if (size - i >= pow(3, j) + 1)
			return pow(3, j);
}

char solve(string s) {
	const size_t size = s.size();

	int inc;
	for (size_t i = 0; i < size - 1; i += inc) {
		inc = getInc(size, i);
		for (size_t j = 0; j < size - i - inc; j++) {
			s[j] = getC(s[j], s[j + inc]);
		}
	}

	return s.at(0);
}
