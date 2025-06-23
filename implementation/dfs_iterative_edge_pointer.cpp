#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

struct edge {
    int to;
    edge* next;
};

vector<edge*> adj;
int n;

void add_edge(int u, int v) {
    edge* new_edge = new edge();
    new_edge->to = v;
    new_edge->next = nullptr;

    if (adj[u] == nullptr) {
        adj[u] = new_edge;
    } else {
        new_edge->next = adj[u];
        adj[u] = new_edge;
    }
}

void dfs_iterative_edge_pointer(int start) {
    vector<bool> visited(n, 0);
    visited[start] = 1;
    stack<edge*> s;
    cout << start << " ";
    s.push(adj[start]);
    while (!s.empty()) {
        auto e = s.top();
        s.pop();
        if (!e) continue;

        int v = e->to;
        s.push(e->next);
        if (!visited[v]) {
            cout << v << " ";
            visited[v] = 1;
            s.push(adj[v]);
        }
    }
    cout << endl;
}

void clear_graph() {
    for (int i = 0; i < n; ++i) {
        edge* current = adj[i];
        while (current) {
            edge* temp = current;
            current = current->next;
            delete temp;
        }
        adj[i] = nullptr;
    }
    adj.clear();
}

int main() {
    // --- 测试用例 1: 简单连通图 ---
    n = 5;
    adj.assign(n, nullptr);

    // 边的添加顺序会影响遍历顺序
    // add_edge(0,1), add_edge(0,2) -> 0的邻接表是 2 -> 1
    add_edge(0, 3);
    add_edge(0, 2);
    add_edge(0, 1);

    add_edge(1, 3);
    add_edge(2, 4);

    cout << "Test Case 1: DFS starting from node 0:" << endl;
    dfs_iterative_edge_pointer(0); // 可能的输出: 0 1 3 2 4
    clear_graph();


    // --- 测试用例 2: 不连通图 ---
    n = 6;
    adj.assign(n, nullptr);

    add_edge(0, 1);
    add_edge(1, 0);
    add_edge(2, 3);
    add_edge(3, 2);
    // 节点4和5是孤立的

    cout << "\nTest Case 2: Disconnected graph" << endl;
    cout << "DFS starting from node 0:" << endl;
    dfs_iterative_edge_pointer(0); // 输出: 0 1

    cout << "DFS starting from node 2:" << endl;
    dfs_iterative_edge_pointer(2); // 输出: 2 3
    clear_graph();


    // --- 测试用例 3: 单节点图 ---
    n = 1;
    adj.assign(n, nullptr);

    cout << "\nTest Case 3: Single node graph" << endl;
    cout << "DFS starting from node 0:" << endl;
    dfs_iterative_edge_pointer(0); // 输出: 0
    clear_graph();

    return 0;
}