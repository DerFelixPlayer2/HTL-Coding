#include "mushrooms.h"
#include <vector>
#include <iostream>

using namespace std;

const int STARTAFTER = 50;

int count_mushrooms(int n) {
	vector<int> A;
	vector<int> B;
	A.push_back(0);

	int count = 1, i = 1;

	if (n == 2) {
		return use_machine({0, 1}) == 0 ? 2 : 1;
	}

	for (; i < n && A.size() < STARTAFTER; i += 2) {
		if (i + 1 < n) {
			int amt = use_machine({i, 0, i + 1});
			switch (amt) {
				case 0:
					A.push_back(i);
					A.push_back(i + 1);
					count += 2;
					break;
				case 1:
					count += 1;
					break;
				case 2:
					B.push_back(i);
					B.push_back(i + 1);
				default:
					break;
			}
		} else {
			count += 1 - use_machine({i, 0});
			return count;
		}
	}

	vector<int> kv;
	for (; i < n;) {
		for (int j: A) {
			kv.push_back(j);
			kv.push_back(i++);

			if (i == n) {
				break;
			}
		}

		cout << kv.size() << endl;
		int k = (int) kv.size() / 2;
		int r = use_machine(kv);

		if (r % 2 == 0) {
			A.push_back(i - 1);
		} else {
			r--;
			k--;
			B.push_back(i - 1);
		}

		count += k - (r / 2);

		if (i == n) {
			break;
		}

		kv.clear();
	}

	cout << "i: " << i << endl;
	cout << "count: " << count << endl;
	return count;
}
