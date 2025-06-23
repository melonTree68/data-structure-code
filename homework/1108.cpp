#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

string in, lev;
unordered_map<char, int> in_map;

struct Node {
    char data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(char d = 0) : data(d) {}
};

void inOrd(Node* r) {
    if (!r) return;
    cout << r->data;
    inOrd(r->left);
    inOrd(r->right);
}

Node* build(const string& lev, int in_l, int in_r) {
    if (in_l > in_r) return nullptr;
    auto r = new Node(lev[0]);
    int r_pos = in_l;
    while (in[r_pos] != lev[0]) ++r_pos;
    string left_lev, right_lev;
    for (int i = 1; i < lev.size(); ++i) (in_map[lev[i]] > r_pos ? right_lev : left_lev) += lev[i];
    r->left = build(left_lev, in_l, r_pos - 1);
    r->right = build(right_lev, r_pos + 1, in_r);
    return r;
}

int main() {
    cin >> in >> lev;
    for (int i = 0; i < in.size(); ++i) in_map[in[i]] = i;
    auto root = build(lev, 0, in.size() - 1);
    inOrd(root);
}