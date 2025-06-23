// general rules for indices: u, v for vertices; i for edges

#include <stdio.h>
#include <queue>
using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

struct input_edge {
    int u, v;
};

struct edge {
    int to, next;
};

int main() {
    int n = read(), m = read();
    int ans = 0;

    auto edges = new edge[2 * m];
    auto inputs = new input_edge[m];
    auto head = new int[n + 1];
    for (int v = 1; v <= n; ++v) head[v] = -1;

    for (int i = 0, cnt = 0; i < m; ++i) {
        int u = read(), v = read();
        inputs[i] = input_edge(u, v);

        edges[cnt] = edge(v, head[u]);
        head[u] = cnt++;
        edges[cnt] = edge(u, head[v]);
        head[v] = cnt++;
    }

    // bfs
    auto dist = new int[n + 1];
    for (int v = 1; v <= n; ++v) dist[v] = -1;
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = head[v]; i != -1; i = edges[i].next) {
            int u = edges[i].to;
            if (dist[u] == -1) {
                q.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    }

    auto pred = new int[n + 1]{}; // pred[u] = number of v's such that there is a shortest path to u that passes through v
    auto alt = new int[n + 1]{}; // count of alternative paths

    for (int v = 1; v <= n; ++v) {
        for (auto i = head[v]; i != -1; i = edges[i].next) {
            int u = edges[i].to;
            if (dist[u] <= dist[v]) ++alt[v];
            if (dist[u] == dist[v] - 1) ++pred[v];
        }
    }

    for (int i = 0; i < m; ++i) {
        int u = inputs[i].u, v = inputs[i].v;
        if (dist[u] > dist[v]) swap(u, v);

        if (dist[v] == dist[u] + 1) {
            if (pred[v] > 1 || alt[v] > 1) ++ans;
        }
        else ++ans;
    }

    printf("%d", ans);
}