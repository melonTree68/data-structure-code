#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, m;
    int total_weight = 0;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj_list(n); // to, weight

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cost; // cost, vertex
    vector<bool> visited(n, 0);
    cost.push({0, 0});

    while (!cost.empty()) {
        auto [w, v] = cost.top();
        cost.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        total_weight += w;
        for (auto& [u, w] : adj_list[v]) cost.push({w, u});
    }

    cout << total_weight;
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
