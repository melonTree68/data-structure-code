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

int main() {
    int n = read(), tmp;
    auto a = new int[n + 9];

    if (n == 0) {
        printf("0");
        return 0;
    }

    for (int i = 0; i < n; ++i) a[i] = read();
    sort(a, a + n);

    int streak = 1;
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] == a[i - 1] + 1) {
            ++streak;
        }
        else if (a[i] != a[i - 1]) {
            ans = max(ans, streak);
            streak = 1;
        }
    }
    printf("%d", max(ans, streak));
    return 0;
}