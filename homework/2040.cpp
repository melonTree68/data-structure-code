#include <iostream>
#include <vector>
using namespace std;

struct NAryTree
{
    int val;
    vector<NAryTree*> children;
};

struct BinaryTree
{
    int val;
    BinaryTree *lson, *rson;
    BinaryTree(const int k) { val = k, lson = rson = NULL; }
};

BinaryTree* Transform(NAryTree* node) {
    auto root = new BinaryTree(node->val);
    if (node->children.empty()) return root;
    root->lson = Transform(node->children[0]);
    auto tmp = root->lson;
    for (int i = 1; i < node->children.size(); ++i) {
        tmp->rson = Transform(node->children[i]);
        tmp = tmp->rson;
    }
    return root;
}