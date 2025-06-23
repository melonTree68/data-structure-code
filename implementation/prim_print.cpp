#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge {
    int from, to, w;
    bool operator<(const edge& other) const {
        return w > other.w;
    }
};

int main() {
    int n, m;
    int total_weight = 0;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj_list(n); // to, weight
    vector<int> prev(n, 0);

    for (int i = 0; i < m; ++i) {
        char u, v;
        int w;
        cin >> u >> v >> w;
        adj_list[u - 'a'].push_back({v - 'a', w});
        adj_list[v - 'a'].push_back({u - 'a', w});
    }

    priority_queue<edge, vector<edge>> cost; // cost, vertex
    vector<bool> visited(n, 0);
    cost.push({0, 0, 0});

    while (!cost.empty()) {
        auto e = cost.top();
        cost.pop();
        if (visited[e.to]) continue;
        visited[e.to] = 1;
        total_weight += e.w;
        prev[e.to] = e.from;
        for (auto [u, w] : adj_list[e.to]) cost.push({e.to, u, w});
        if (e.from != e.to) cout << "\\item Add the edge with endpoints $" << char(e.from + 'a') << "," << char(e.to + 'a') << "$. \n";
    }

    cout << "Total weight: " << total_weight;
    return 0;
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
