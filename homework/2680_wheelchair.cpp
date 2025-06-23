#include <stdio.h>
#include <algorithm>
using namespace std;

int a[int(1e5) + 9];

inline int read() {
    int x = 0, c = getchar_unlocked();
    while (c < '0' || c > '9') c = getchar_unlocked();
    for (; c >= '0' && c <= '9'; c = getchar_unlocked()) x = x * 10 + (c - '0');
    return x;
}

inline void write(int x) {
    char buf[16];
    int len = 0;
    if (x == 0) {
        buf[len++] = '0';
    } else {
        while (x > 0) {
            buf[len++] = '0' + (x % 10);
            x /= 10;
        }
        reverse(buf, buf + len);
    }
    buf[len++] = '\n';
    fwrite(buf, 1, len, stdout);
}

int main() {
    int n = read(), m = read(), q;
    for (int i = 0; i < n; ++i) a[i] = read();
    sort(a, a + n);
    while (m--) {
        q = read();
        write(lower_bound(a, a + n, q) - a);
    }
}