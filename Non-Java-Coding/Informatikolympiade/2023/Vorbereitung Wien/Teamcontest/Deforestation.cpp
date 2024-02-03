
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int w;
	vector<Node*> children;
};

Node* head = nullptr;

int cuts = 0;
int W;

Node* buildTree() {
	int m, n;
	cin >> m >> n;
	Node* node = new Node({m});
	for (int i = 0; i < n; i++) {
		node->children.push_back(buildTree());
	}
	return node;
}

int dfs(Node* node) {
	if (node == nullptr) return 0;
	int sumNodes = 0;
	for (Node* child : node->children) {
		int w = dfs(child);

		if (w == W) {
			cuts++;
			child->w = 0;
			child->children.clear();
			child->children.shrink_to_fit();
			w = 0;
		}
		sumNodes += w;
	}

	if (sumNodes > W) {
		sort(node->children.begin(), node->children.end(),
			 [](Node* a, Node* b) { return a->w < b->w; });

		while (sumNodes > W) {
			sumNodes -= node->children.back()->w;
			node->children.pop_back();
			cuts++;
		}
	}

	if (sumNodes == W) {
		cuts++;
		node->children.clear();
		node->children.shrink_to_fit();
		sumNodes = 0;
	}

	int sum = sumNodes + node->w;
	if (sum > W) {
		while (sum > W) {
			sum -= W;
			cuts++;
		}

		node->w = sum;
		node->children.clear();
		node->children.shrink_to_fit();
		return sum;
	}

	node->w = sum;
	node->children.clear();
	node->children.shrink_to_fit();
	return sum;
}

int main() {
	cin >> W;

	head = buildTree();

	dfs(head);

	cout << cuts + 1 << endl;
}