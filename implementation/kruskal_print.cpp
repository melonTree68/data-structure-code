#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int u, v, w;
	bool operator<(const edge& other) {
		return w < other.w;
	}
};

vector<edge> edges;
vector<int> parent, rank_;

void makeset(int n) {
	parent = vector<int>(n);
	for (int i = 0; i < n; ++i)
		parent[i] = i;
	rank_ = vector<int>(n);
}

int find(int x) {
	return parent[x] = x == parent[x] ? x : find(parent[x]);
}

bool unite(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return false;
	if (rank_[x] > rank_[y]) {
		parent[y] = x;
	} else {
		parent[x] = y;
		if (rank_[x] == rank_[y]) ++rank_[y];
	}
	return true;
}

int main() {
	int total_weight = 0;
	int n, m;
	cin >> n >> m;
	makeset(n);
	for (int i = 0; i < m; ++i) {
		char u, v;
		int w;
		cin >> u >> v >> w;
		edges.push_back(edge(u - 'a', v - 'a', w));
	}

	sort(edges.begin(), edges.end());
	for (auto& e : edges)
		if (unite(e.u, e.v)) {
			total_weight += e.w;
			cout << "\\item Add the edge with endpoints $" << char(e.u + 'a') << "," << char(e.v + 'a') << "$. \n";
		}
	cout << "Total weight: " << total_weight;
}

// sample input 1: output 10
// 5 7
// 0 1 10
// 0 2 1
// 0 3 4
// 1 2 2
// 1 4 5
// 2 3 8
// 3 4 3

// sample input 2: output 6
// 4 5
// 0 1 1
// 0 2 4
// 1 2 2
// 1 3 6
// 2 3 3

// sample input 3: output 16
// 6 9
// 0 1 4
// 0 2 1
// 0 3 3
// 1 2 4
// 1 3 4
// 2 3 2
// 2 4 4
// 3 4 6
// 4 5 5
