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

int charToIndex(char c) { // a ... z A ... Z
    if (c >= 'a') return c - 'a';
    else return c - 'A' + 26;
}

class Trie {
private:
    struct TrieNode {
        int count = 0;
        TrieNode* children[52];
        TrieNode() { for (auto& node : children) node = nullptr; }
    };

    TrieNode* root = new TrieNode();

public:
    void insert(char s[]) {
        auto node = root;
        for (int i = 0; s[i]; ++i) {
            int idx = charToIndex(s[i]);
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
            ++node->count;
        }
    }

    int count(char s[]) {
        auto node = root;
        for (int i = 0; s[i]; ++i) {
            int idx = charToIndex(s[i]);
            if (!node->children[idx]) return 0;
            node = node->children[idx];
        }
        return node->count;
    }
};

int main() {
    int T = read(), n, q;
    char s[3000000];
    while (T--) {
        Trie trie;
        n = read();
        q = read();
        for (int i = 0; i < n; ++i) {
            scanf("%s", s);
            trie.insert(s);
        }
        for (int i = 0; i < q; ++i) {
            scanf("%s", s);
            printf("%d\n", trie.count(s));
        }
    }
}