#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, x, y;
    cin >> n >> m;
    vector<bool> v1(n + 1);
    vector<int> v2(n + 1);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        v1[x] = 1;
        ++v2[x];
    }
    for (int i = 1; i <= n; ++i) if (!v1[i] && v2[i] == n - 1) { cout << i; }
}