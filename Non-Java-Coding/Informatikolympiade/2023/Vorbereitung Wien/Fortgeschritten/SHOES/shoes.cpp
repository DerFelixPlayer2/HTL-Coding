#include "shoes.h"
#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <vector>
#include <queue>

#ifdef DEV
#define PRINT
#define TIME
#endif

#define MAX_SIZE 200005

using namespace std;

auto c = 0ll;

inline void print(std::vector<int> &s) {
#ifdef PRINT
	for (int i: s) cout << i << " ";
	cout << "  ->  " << c << endl;
#endif
}

// A utility function to get the middle index from corner indexes.
int getMid(int s, int e) { return s + (e - s) / 2; }

/* A recursive function to get the sum of values in the given range
    of the array. The following are parameters for this function.

    st --> Pointer to segment tree
    si --> Index of current node in the segment tree. Initially
            0 is passed as root is always at index 0
    ss & se --> Starting and ending indexes of the segment represented
                by current node, i.e., st[si]
    qs & qe --> Starting and ending indexes of query range */
int getSumUtil(int *st, int ss, int se, int qs, int qe, int si) {
	// If segment of this node is a part of given range, then return
	// the sum of the segment
	if (qs <= ss && qe >= se)
		return st[si];

	// If segment of this node is outside the given range
	if (se < qs || ss > qe)
		return 0;

	// If a part of this segment overlaps with the given range
	int mid = getMid(ss, se);
	return getSumUtil(st, ss, mid, qs, qe, 2 * si + 1) +
		   getSumUtil(st, mid + 1, se, qs, qe, 2 * si + 2);
}

// Return sum of elements in range from index qs (query start)
// to qe (query end). It mainly uses getSumUtil()
int getSum(int *st, int n, int qs, int qe) {
	return getSumUtil(st, 0, n - 1, qs, qe, 0);
}

/* A recursive function to update the nodes which have the given
index in their range. The following are parameters
    st, si, ss and se are same as getSumUtil()
    i --> index of the element to be updated. This index is
            in the input array.
diff --> Value to be added to all nodes which have i in range */
void updateValueUtil(int *st, int ss, int se, int i, int diff, int si) {
	// Base Case: If the input index lies outside the range of
	// this segment
	if (i < ss || i > se)
		return;

	// If the input index is in range of this node, then update
	// the value of the node and its children
	st[si] = st[si] + diff;
	if (se != ss) {
		int mid = getMid(ss, se);
		updateValueUtil(st, ss, mid, i, diff, 2 * si + 1);
		updateValueUtil(st, mid + 1, se, i, diff, 2 * si + 2);
	}
}

// The function to update a value in input array and segment tree.
// It uses updateValueUtil() to update the value in segment tree
void updateValue(int *st, int n, int i, int new_val) {
	// Get the difference between new value and old value
	int diff = new_val - st[i];

	cout << "before update: " << endl;
	for (int i = 0; i < MAX_SIZE; i++) {
		cout << st[i] << " ";
	}
	cout << endl;

	// Update the value in array
	st[i] = new_val;

	// Update the values of nodes in segment tree
	updateValueUtil(st, 0, n - 1, i, diff, 0);

	cout << "after update: " << endl;
	for (int i = 0; i < MAX_SIZE; i++) {
		cout << st[i] << " ";
	}
	cout << endl;
}

// A recursive function that constructs Segment Tree for array[ss..se].
// si is index of current node in segment tree st
int constructSTUtil(int ss, int se, int *st, int si) {
	// If there is one element in array, store it in current node of
	// segment tree and return
	if (ss == se) {
		st[si] = 1;
		return 1;
	}

	// If there are more than one elements, then recur for left and
	// right subtrees and store the sum of values in this node
	int mid = getMid(ss, se);
	st[si] = constructSTUtil(ss, mid, st, si * 2 + 1) +
			 constructSTUtil(mid + 1, se, st, si * 2 + 2);
	return st[si];
}

/* Function to construct segment tree from given array. This function
allocates memory for segment tree and calls constructSTUtil() to
fill the allocated memory */
int *constructST(int n) {

	// Allocate memory
	int *st = new int[MAX_SIZE];

	// Fill the allocated memory st
	constructSTUtil(0, MAX_SIZE, st, 0);

	// Return the constructed segment tree
	return st;
}

void print_t(int *st, int n) {
#ifdef PRINT
	cout << "tree: ";
	for (int i = 0; i < 4 * n; i++) cout << st[i] << " ";
	cout << endl;
#endif
}

int pop_closest(queue<int> &q, int item) {
	return q.front();
	/*int first = q.front(), v, dist = abs(item - first), v_min = first;
	q.pop();
	q.push(first);
	while ((v = q.front()) != first) {
		int t = abs(item - v);
		if (t < dist) {
			dist = t;
			v_min = v;
		}
		q.push(v);
	}
	return v_min;/**/
}

long long count_swaps(std::vector<int> s) {
	ios_base::sync_with_stdio(false);

	auto rmap = new map<int, queue<int>>();
	//auto lmap = new map<int, queue<int>>();
	for (int i = 0; i < s.size(); i++) {
		if (s[i] > 0) {
			if (rmap->find(s[i]) == rmap->end()) {
				auto q = new queue<int>();
				q->push(i);
				rmap->insert({s[i], *q});
			} else {
				rmap->at(s[i]).push(i);
			}
		} else {
			/*if (lmap->find(-s[i]) == lmap->end()) {
				auto q = new queue<int>();
				q->push(i);
				lmap->insert({-s[i], *q});
			} else {
				lmap->at(-s[i]).push(i);
			}*/
		}
	}

	int n = (int) s.size();
	c = 0;

#ifdef PRINT
	cout << "--" << endl;
#endif

#if defined(TIME) && defined(PRINT)
	auto start = chrono::high_resolution_clock::now();
#endif

	int *st = constructST(n);
	print_t(st, n);


	for (int i = 0; i < n; i++) {
		if (s[i] < 0) {
			int item = pop_closest(rmap->at(-s[i]), i);
			cout << "item: " << item << endl;
			cout << "i: " << i << endl;
			cout << "s[i]: " << s[i] << endl;

			if (i == item - 1) {
				//	cout << "skip" << endl;
				continue;
			}

			cout << "c: " << c << " -> ";
			c += getSum(st, n, min(i, item), max(i, item));
			if (i > item) c--;
			cout << c << endl;

			//inc_value(st, n, i);
			//dec_value(st, n, item);
			updateValue(st, n, item, 0);

			print_t(st, n);
		}
	}




	/*for (int i = 0; i < n; i++) {
		cout << "i: " << i << " s[i]: " << s[i] << endl;


		if (s[i] < 0) {
			int j = rmap->at(-s[i]).front();
			rmap->at(-s[i]).pop();
			cout << "j: " << j << endl;

			if (i + 1 == j) {
				cout << "skip" << endl;
				continue;
			}

			cout << "c: " << c << " -> ";
			c += get_sum_in_range(st, n, min(i, j), max(i, j));
			if (i < j) c--;
			cout << c << endl;

			inc_value(st, n, min(i, j));
			dec_value(st, n, max(i, j));

			print_t(st, n);
		}
		// print(s);
	}
*/

#if defined(TIME) && defined(PRINT)
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Time: " << duration.count() << " microseconds" << endl;
#endif
#ifdef PRINT
	cout << "--" << endl;
#endif

	return c;
}
