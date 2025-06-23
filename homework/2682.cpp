#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 100005;

char buffer[MAXN][105];
char* p[MAXN];
char t[105], t_hi[106];

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

inline void read(char* s) {
    char c = getchar_unlocked();
    while (c <= ' ') c = getchar_unlocked();
    while (c > ' ') {
        *s++ = c;
        c = getchar_unlocked();
    }
    *s = '\0';
}

inline void write(int x) {
    if (x == 0) {
        putchar_unlocked('0');
        putchar_unlocked('\n');
        return;
    }
    char buf[12];
    int i = 10;
    buf[11] = '\n';
    while (x) {
        buf[i--] = x % 10 + '0';
        x /= 10;
    }
    while (++i < 12) putchar_unlocked(buf[i]);
}

int lowerBound(char* arr[], int n, const char* key) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (strcmp(arr[m], key) < 0)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

int main() {
    int T = read(), n, q;

    while (T--) {
        n = read();
        q = read();

        for (int i = 0; i < n; ++i) {
            read(buffer[i]);
            p[i] = buffer[i];
        }

        std::sort(p, p + n, [](const char* a, const char* b) {
            return strcmp(a, b) < 0;
        });

        while (q--) {
            read(t);
            int len = strlen(t);
            memcpy(t_hi, t, len);
            t_hi[len] = '{';
            t_hi[len + 1] = '\0';

            int l = lowerBound(p, n, t);
            int r = lowerBound(p, n, t_hi);
            write(r - l);
        }
    }

    return 0;
}
