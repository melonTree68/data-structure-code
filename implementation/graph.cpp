#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Graph {
    int verts;
    vector<vector<int>> adj_list;

public:
    Graph(int v) : verts(v), adj_list(v) {}

    // Add an edge from u to v
    void AddEdge(int u, int v) {
        if (u >= verts || v >= verts) return;
        adj_list[u].push_back(v); 
    }

    // Remove the edge from u to v
    void RemoveEdge(int u, int v) {
        if (u >= verts || v >= verts) return;
        auto& src = adj_list[u];
        src.erase(remove(src.begin(), src.end(), v), src.end());
    }

    void AddVertex() {
        adj_list.push_back({});
        ++verts;
    }

    void RemoveVertex(int v) {
        if (v >= verts) return;
        --verts;

        // remove all incoming edges
        for (auto& edges : adj_list) edges.erase(remove(edges.begin(), edges.end(), v), edges.end());

        // remove outgoing edges
        adj_list.erase(adj_list.begin() + v);
        
        // rename vertices with greater index
        for (auto& edges : adj_list) for (auto& u : edges) if (u > v) --u;
    }

    void PrintGraph() {
        for (int i = 0; i < verts; ++i) {
            cout << "Vertex " << i << " has neighbors: ";
            for (auto j : adj_list[i]) cout << j << " ";
            cout << endl;
        }
    }

    const vector<int>& neighbors(int v) const {
        return adj_list[v];
    }

    int size() const {
        return verts;
    }

    void DFS(int start, bool visited[]) {
        visited[start] = true;
        cout << start << " ";
        for (auto v : adj_list[start]) if (!visited[v]) DFS(v, visited);
    }

    // void DFS() { // by recursion
    //     auto visited = new bool[verts];
    //     for (int i = 0; i < verts; ++i) visited[i] = false;
    //     for (int i = 0; i < verts; ++i) if (!visited[i]) DFS(i, visited); 
    // }

    void DFS() { // by stack
        if (!verts) return;
        auto visited = new bool[verts];
        for (int i = 0; i < verts; ++i) visited[i] = false;
        stack<int> s;
        s.push(0);
        while (!s.empty()) {
            auto v = s.top();
            s.pop();
            visited[v] = true;
            cout << v << " ";
            for (auto u : adj_list[v]) if (!visited[u]) s.push(u);
        }
    }
};

// int main() { // test DFS
//     Graph g(5);

//     g.AddEdge(0, 1);
//     g.AddEdge(0, 2);
//     g.AddEdge(1, 3);
//     g.AddEdge(1, 4);

//     cout << "Graph structure:" << endl;
//     g.PrintGraph();

//     cout << "\nDFS starting from node 0:" << endl;
//     g.DFS();

//     return 0;
// }

// int main() { // test basic operations
//     Graph g(3);
//     g.AddEdge(0, 1);
//     g.AddEdge(1, 2);
//     g.PrintGraph();

//     cout << "--- After adding a vertex and an edge ---" << endl;
//     g.AddVertex(); // 新增节点 3
//     g.AddEdge(2, 3);
//     g.PrintGraph();

//     cout << "--- After removing edge 1->2 ---" << endl;
//     g.RemoveEdge(1, 2);
//     g.PrintGraph();

//     cout << "--- After removing vertex 1 ---" << endl;
//     g.RemoveVertex(1); // 删除节点1
//     g.PrintGraph();

//     return 0;
// }
