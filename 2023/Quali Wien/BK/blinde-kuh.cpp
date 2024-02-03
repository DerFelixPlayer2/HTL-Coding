#include "blinde-kuh.h"
#include <cmath>
#include <iostream>

using namespace std;

void log(const int n, const bool overshooting, const bool resetting, const int low, const int high, const int lowh,
		 const int highh,
		 const int hit = -1) {
#ifdef DEV
	if (overshooting) cout << "O ";
	if (resetting) cout << "R ";
	for (int i = 0; i < n; i++) {
		if (i != hit && i != low && i != high && i != highh && i != lowh) continue;
		bool b = false;
		cout << "[";
		if (i == hit) {
			cout << "*";
			b = true;
		}
		if (i == low) {
			cout << "l";
			b = true;
		}
		if (i == high) {
			cout << "h";
			b = true;
		}
		if (i == lowh) {
			cout << "L";
			b = true;
		}
		if (i == highh) {
			cout << "H";
			b = true;
		}
		if (b) cout << i;
		cout << "] ";
		// cout << i << "] ";
	}
	cout << "\n";
#endif
}

void blinde_kuh(int n) {
	const int x = 0;
	int lowY = 0, highY = n - 1;
	int hitterLow = 0, hitterHigh = n - 1;
	bool high = true, overshooting = false;

	ios_base::sync_with_stdio(false);

	log(n, false, false, lowY, highY, hitterLow, hitterHigh, hitterLow);
	log(n, false, false, lowY, highY, hitterLow, hitterHigh, hitterHigh);

	hit(x, hitterLow);
	while (true) {
		const bool closerThanBefore = hit(x, high ? hitterHigh : hitterLow);
		const int offset = ceil(((highY+1) - lowY) / 2);

		if (closerThanBefore) {

			if (high) {
				cout << lowY + offset << " = " << lowY << " + " << offset << endl;
				lowY = lowY + offset;

				if (overshooting) {
					cout << lowY - (hitterHigh - highY) << " = " << lowY << " - (" << hitterHigh << " - " << highY
						 << ")" << endl;
					hitterLow = lowY - (hitterHigh - highY);
				}
			} else {
				cout << highY - offset << " = " << highY << " - " << offset << endl;
				highY = highY - offset;

				if (overshooting) {
					cout << highY + (lowY - hitterLow) << " = " << highY << " + (" << lowY << " - " << hitterLow << ")" << endl;
					hitterHigh = highY + (lowY - hitterLow);
				}
			}
			high = !high;
		} else {

			if (high) {

				if (!overshooting && lowY - offset >= 0) {
					overshooting = true;
					hitterLow = lowY - offset;
					hitterHigh = highY;
				}

				if (overshooting) {
					cout << highY + (lowY - hitterLow) << " = " << highY << " + (" << lowY << " - " << hitterLow << ")" << endl;
					hitterHigh = highY + (lowY - hitterLow);
				}
				cout << highY - offset << " = " << highY << " - " << offset << endl;
				highY = highY - offset;

			} else {

				if (!overshooting && highY + offset < n) {
					overshooting = true;
					hitterLow = lowY;
					hitterHigh = highY + offset;
				}

				if (overshooting) {
					cout << lowY - (hitterHigh - highY) << " = " << lowY << " - (" << hitterHigh << " - " << highY
						 << ")" << endl;
					hitterLow = lowY - (hitterHigh - highY);
				}
				cout << lowY + offset << " = " << lowY << " + " << offset << endl;
				lowY = lowY + offset;

			}

			// high = !high;
			if (!overshooting) {
				high = true;
				hit(x, lowY);
				log(n, false, true, lowY, highY, hitterLow, hitterHigh, lowY);
			} else high = !high;
		}

		if (!overshooting) {
			hitterLow = lowY;
			hitterHigh = highY;
		}

		log(n, overshooting, false, lowY, highY, hitterLow, hitterHigh, high ? hitterHigh : hitterLow);

		if (lowY == highY) break;
	}

	const int y = lowY;
	int lowX = 0, highX = n - 1;
	high = true;

	hit(lowX, y);
	while (true) {
		const bool closerThanBefore = hit(high ? highX : lowX, y);
		const int offset = ceil(((highX + 1) - lowX) / 2);

		if (closerThanBefore) {
			if (high) {
				lowX = lowX + offset;
			} else {
				highX = highX - offset;
			}
			high = !high;
		} else {
			if (high) {
				hit(lowX, y);
				highX = highX - offset;
			} else {
				lowX = lowX + offset;
				hit(lowX, y);
				high = true;
			}
		}

		if (lowX == highX) {
			// hit(lowX, y + 1);
			// hit(lowX, y - 1);
			// hit(lowX, y + 2);
			// hit(lowX, y - 2);
			return;
		}
	}
}