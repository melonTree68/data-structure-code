#include <algorithm>
#include <stdio.h>
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

int partition(int arr[], int l, int r) {
    int k = l;
    for (int i = l; i < r; ++i) if (arr[i] < arr[r]) swap(arr[i], arr[k++]);
    swap(arr[k], arr[r]);
    return k;
}

void quick_sort(int arr[], int l, int r) {
    if (l >= r) return;
    int m = partition(arr, l, r);
    quick_sort(arr, l, m - 1);
    quick_sort(arr, m + 1, r);
}

int main() {
    int n = read(), m = read(), q;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) arr[i] = read();
    quick_sort(arr, 0, n - 1);

    for (int i = 0; i < m; ++i) {
        q = read();
        int l = 0, r = n;
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] < q) l = m + 1;
            else r = m;
        }
        printf("%d\n", l);
    }
}