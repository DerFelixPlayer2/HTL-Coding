#pragma once
#include <vector>

void alice(std::vector<int> p);
int bob(int n, int l, int r);

void send(bool b);
bool receive();

inline void send(unsigned long long a, int n) {
	for (int i = 0; i < n; i++) send((a & (1ull << i)) != 0);
}
inline auto receive(int n) {
	unsigned long long a = 0;
	for (int i = 0; i < n; i++)
		if (receive()) a |= (1ull << i);
	return a;
}
