#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main() {
    int n, u, v, x, y;
    cin >> n;
    auto left = new int[n + 9]{};
    auto right = new int[n + 9]{};
    auto parent = new int[n + 9]{};
    auto depth = new int[n + 9]{0, 1};
    auto depth_cnt = new int[n + 9]{};

    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        parent[v] = u;
        if (left[u]) right[u] = v;
        else left[u] = v;
    }
    cin >> x >> y;

    function<void(int)> dfs = [&](int node) -> void {
        if (!node) return;
        depth[left[node]] = depth[right[node]] = depth[node] + 1;
        ++depth_cnt[depth[node]];
        dfs(left[node]);
        dfs(right[node]);
    };
    dfs(1);

    int breadth = 0, max_depth = 0;
    for (int i = 1; i <= n + 1; ++i) {
        breadth = max(breadth, depth_cnt[i]);
        max_depth = max(max_depth, depth[i]);
    }
    cout << max_depth << endl << breadth << endl;

    vector<int> px, py;
    while (x) {
        px.push_back(x);
        x = parent[x];
    }
    while (y) {
        py.push_back(y);
        y = parent[y];
    }
    
    while (!px.empty() && !py.empty() && px.back() == py.back()) {
        px.pop_back();
        py.pop_back();
    }
    cout << px.size() * 2 + py.size();
}