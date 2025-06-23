#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

vector<int> bfs(vector<vector<int>> adj_list, int start) {
    vector<int> dist(adj_list.size(), -1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj_list[u]) {
            if (dist[v] == -1) {
                q.push(v);
                dist[v] = dist[u] + 1;
            }
        }
    }
    return dist;
}

int main() {
    int n, m, o, a, b;
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &o, &a, &b);

    vector<vector<int>> adj_list(n + 1); // 0 is dummy
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    auto d = bfs(adj_list, o);
    auto da = bfs(adj_list, a);
    auto db = bfs(adj_list, b);

    int max_depart = -1;
    for (int i = 1; i <= n; ++i) {
        if (d[i] > max_depart && d[i] + da[i] == d[a] && d[i] + db[i] == d[b]) max_depart = d[i];
    }
    printf("%d", max_depart);
}