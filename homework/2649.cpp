#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    auto parent = new int[n + 9]{};
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        parent[a] = parent[b] = i;
    }

    vector<int> px, py;
    while (x != 0) {
        px.push_back(x);
        x = parent[x];
    }
    while (y != 0) {
        py.push_back(y);
        y = parent[y];
    }

    int tmp = 0;
    while (!px.empty() && !py.empty() && px.back() == py.back()) {
        tmp = px.back();
        px.pop_back();
        py.pop_back();
    }
    cout << tmp;
}