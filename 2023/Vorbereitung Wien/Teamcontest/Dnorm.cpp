#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

vector<double> X;
vector<int> A;

const double b = .99999999999999999999e-6;

double findD(int a0) {
	if (a0 > 10000) {
		return -1;
	}
	double d = a0 / X[0];
	A.push_back(a0);

	for (int i = 1; i < X.size(); i++) {
		double ai = X[i] * d;
		A.push_back((int)ai);
		char as[100];
		sprintf(as, "%.6f", ai);
		double ai2 = atof(as);
		if (ai2 != (int)ai2 || ai2 < 1) {
			A.clear();
			A.shrink_to_fit();
			return findD(a0 + 1);
		}
	}

	for (int i = 0; i < A.size(); i++) {
		cout << A[i] << endl;
	}

	return d;
}

int main() {
	int n;
	cin >> n;
	cout << setprecision(15);

	for (int i = 0; i < n; i++) {
		long double x;
		cin >> x;
		X.push_back(x);
	}

	double d = findD(1);
}
