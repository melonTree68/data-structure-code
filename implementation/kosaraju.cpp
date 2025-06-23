// Kosaraju's algorithm for finding strongly connected components
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj_list, adj_list_rev;
vector<bool> visited;
vector<int> post_ord;

void visit(int v) {
    visited[v] = true;
    for (auto u : adj_list_rev[v]) if (!visited[u]) visit(u);
    post_ord.push_back(v);
}

void dfs() {
    visited = vector<bool>(adj_list_rev.size());
    for (int i = 0; i < adj_list_rev.size(); ++i) {
        if (!visited[i]) visit(i);
    }
}

void visit_scc(int v) {
    visited[v] = true;
    cout << char(v + 'a');
    for (auto u : adj_list[v]) if (!visited[u]) visit_scc(u);
}

void dfs_scc() {
    visited = vector<bool>(adj_list.size());
    for (auto i : post_ord) {
        if (!visited[i]) {
            cout << endl;
            visit_scc(i);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    adj_list = adj_list_rev = vector<vector<int>>(n);
    for (int i = 0; i < m; ++i) {
        char u, v;
        cin >> u >> v;
        adj_list[u - 'a'].push_back(v - 'a');
        adj_list_rev[v - 'a'].push_back(u - 'a');
    }

    dfs();
    reverse(post_ord.begin(), post_ord.end());
    dfs_scc();
}