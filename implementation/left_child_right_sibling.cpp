#include <iostream>
#include <vector>
using namespace std;

struct Tree {
    int val;
    vector<Tree*> children;
    Tree(int d = 0) : val(d) {}
};

struct BinaryTree {
    int val;
    BinaryTree* lson = nullptr;
    BinaryTree* rson = nullptr;
    BinaryTree(int d = 0) : val(d) {}
};

BinaryTree* Tree2BinaryTree(Tree* root) {
    auto r = new BinaryTree(root->val);
    if (root->children.empty()) return r;
    r->lson = Tree2BinaryTree(root->children[0]);

    auto tmp = r->lson;
    for (int i = 1; i < root->children.size(); ++i) {
        auto next_child = Tree2BinaryTree(root->children[i]);
        tmp->rson = next_child;
        tmp = next_child;
    }

    return r;
}

Tree* BinaryTree2Tree(BinaryTree* root) {
    auto r = new Tree(root->val);
    if (!root->lson) return r;
    r->children.push_back(BinaryTree2Tree(root->lson));
    auto tmp = root->lson->rson;
    while (tmp) {
        r->children.push_back(BinaryTree2Tree(tmp));
        tmp = tmp->rson;
    }
    return r;
}

void TraverseTree(Tree* r) {
    cout << r->val << " ";
    for (auto child : r->children) TraverseTree(child);
}

void TraverseBinaryTree(BinaryTree* r) {
    if (!r) return;
    cout << r->val << " ";
    TraverseBinaryTree(r->lson);
    TraverseBinaryTree(r->rson);
}

int main() {
    // 构造一个简单的Tree:
    //      1
    //    / | \
    //   2  3  4
    //     / \
    //    5   6

    Tree* root = new Tree(1);
    root->children.push_back(new Tree(2));
    Tree* node3 = new Tree(3);
    node3->children.push_back(new Tree(5));
    node3->children.push_back(new Tree(6));
    root->children.push_back(node3);
    root->children.push_back(new Tree(4));

    cout << "Original Tree preorder:" << endl;
    TraverseTree(root);
    cout << endl << endl;

    // 转成二叉树
    BinaryTree* b_root = Tree2BinaryTree(root);
    cout << "Binary Tree preorder:" << endl;
    TraverseBinaryTree(b_root);
    cout << endl << endl;

    // 再转回多叉树
    Tree* recovered = BinaryTree2Tree(b_root);
    cout << "Recovered Tree preorder:" << endl;
    TraverseTree(recovered);
    cout << endl;

    return 0;
}
