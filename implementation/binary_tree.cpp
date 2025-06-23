#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int d = -1) : data(d) {}
};

class BinaryTree {
  private:
    Node* root;

    void _DelTree(Node* t) {
        if (!t) return;
        _DelTree(t->left);
        _DelTree(t->right);
        delete t;
    }

    int _size(Node* t) {
        if (!t) return 0;
        return _size(t->left) + _size(t->right) + 1;
    }

    int _height(Node* t) {
        if (!t) return 0;
        return max(_height(t->left), _height(t->right)) + 1;
    }

    void _inOrder(Node* t) {
        if (!t) return;
        _inOrder(t->left);
        cout << t->data << " ";
        _inOrder(t->right);
    }

  public:
    BinaryTree(Node* r = nullptr) : root(r) {}

    BinaryTree(const vector<int>& v) : root(nullptr) { // construct by level order
        if (v.empty()) return;
        root = new Node(v[0]);
        queue<Node*> q;
        q.push(root);
        for (int i = 1; i < v.size(); i += 2) {
            auto tmp = q.front();
            q.pop();
            if (v[i] != -1) q.push(tmp->left = new Node(v[i]));
            if (i + 1 < v.size() && v[i + 1] != -1) q.push(tmp->right = new Node(v[i + 1]));
        }
    }

    BinaryTree(const vector<int>& pre_ord, const vector<int>& in_ord) { // construct by pre-order and in-order traversal
        function<Node*(int, int, int, int)> build = [&](int pre_l, int pre_r, int in_l, int in_r) -> Node* {
            if (pre_l > pre_r || in_l > in_r) return nullptr;
            int pos = in_l;
            while (in_ord[pos] != pre_ord[pre_l]) ++pos;
            int left_size = pos - in_l;
            auto tmp = new Node(pre_ord[pre_l]);
            tmp->left = build(pre_l + 1, pre_l + left_size, in_l, pos - 1);
            tmp->right = build(pre_l + left_size + 1, pre_r, pos + 1, in_r);
            return tmp;
        };
        root = build(0, pre_ord.size() - 1, 0, in_ord.size() - 1);
    }

    ~BinaryTree() { _DelTree(root); }

    bool empty() { return root; }

    int size() { return _size(root); }

    int height() { return _height(root); }

    void inOrder() { _inOrder(root); }

    void levelOrder() {
        queue<Node*> q;
        q.push(root);
        while (!(q.empty())) {
            auto tmp = q.front();
            q.pop();
            cout << tmp->data << " ";
            if (tmp->left) q.push(tmp->left);
            if (tmp->right) q.push(tmp->right);
        }
    }
};

int main() {
    // 测试用例 1：使用层序遍历数组创建二叉树
    vector<int> levelOrder = {1, 2, 3, 4, 5, -1, -1, 6, 7};
    BinaryTree tree1(levelOrder);

    cout << "Tree 1 In-Order Traversal: ";
    tree1.inOrder(); // 应该输出 6 4 7 2 5 1 3
    cout << endl;

    cout << "Tree 1 Level-Order Traversal: ";
    tree1.levelOrder(); // 应该输出 1 2 3 4 5 6 7
    cout << endl;

    cout << "Tree 1 Size: " << tree1.size() << endl;     // 应该输出 7
    cout << "Tree 1 Height: " << tree1.height() << endl; // 应该输出 4

    // 测试用例 2：使用前序和中序遍历数组创建二叉树
    vector<int> preOrder = {1, 2, 4, 5, 3};
    vector<int> inOrder = {4, 2, 5, 1, 3};
    BinaryTree tree2(preOrder, inOrder);

    cout << "Tree 2 In-Order Traversal: ";
    tree2.inOrder(); // 应该输出 4 2 5 1 3
    cout << endl;

    cout << "Tree 2 Level-Order Traversal: ";
    tree2.levelOrder(); // 应该输出 1 2 3 4 5
    cout << endl;

    cout << "Tree 2 Size: " << tree2.size() << endl;     // 应该输出 5
    cout << "Tree 2 Height: " << tree2.height() << endl; // 应该输出 3

    return 0;
}