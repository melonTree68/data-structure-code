#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class binary_search_tree {
private:
    struct Node {
        int val;
        Node* left;
        Node* right;
        Node(int v, Node* l = nullptr, Node* r = nullptr) : val(v), left(l), right(r) {}
    };

    Node* root = nullptr;

    void del(Node* r) {
        if (!r) return;
        del(r->left);
        del(r->right);
        delete r;
    }

    bool find(int x, Node* r) {
        if (!r) return false;
        if (x == r->val) return true;
        return x < r->val ? find(x, r->left) : find(x, r->right);
    }

    void insert(int x, Node*& r) {
        if (!r) r = new Node(x);
        else if (x != r->val) x < r->val ? insert(x, r->left) : insert(x, r->right);
    }

    void remove(int x, Node*& r) {
        if (!r) return;
        if (x == r->val) {
            if (!r->left && !r->right) {
                delete r;
                r = nullptr;
            }
            else if (r->left && r->right) {
                // right-most node in left subtree
                Node** ptr = &r->left;
                while ((*ptr)->right) ptr = &(*ptr)->right;
                r->val = (*ptr)->val;
                remove(r->val, *ptr);
            }
            else {
                auto tmp = r;
                r = r->left ? r->left : r->right;
                delete tmp;
            }
        }
        else {
            x < r->val ? remove(x, r->left) : remove(x, r->right);
        }
    }

public:
    void print_inorder() {
        if (!root) {
            cout << endl;
            return;
        }
        stack<pair<Node*, int>> s;
        s.push({root, 0});
        while (!s.empty()) {
            auto [r, k] = s.top();
            s.pop();
            if (k) cout << r->val << " ";
            else {
                if (r->right) s.push({r->right, 0});
                s.push({r, 1});
                if (r->left) s.push({r->left, 0});
            }
        }
        cout << endl;
    }

    ~binary_search_tree() { del(root); }

    bool find(int x) { return find(x, root); }

    void insert(int x) { insert(x, root); }

    void remove(int x) { remove(x, root); }
};

int main() {
    binary_search_tree bst;

    cout << "=== 插入元素 ===" << endl;
    vector<int> values_to_insert = {20, 10, 30, 5, 15, 25, 35, 10, 30};
    for (int val : values_to_insert) {
        cout << "插入 " << val << endl;
        bst.insert(val);
    }

    cout << "\n中序遍历:" << endl;
    bst.print_inorder();

    cout << "\n=== 查找元素 ===" << endl;
    vector<int> values_to_find = {15, 100, 5, 22};
    for (int val : values_to_find) {
        cout << "查找 " << val << ": ";
        cout << bst.find(val) << endl;
    }

    cout << "\n=== 删除叶子节点 ===" << endl;
    bst.remove(5); // 叶子节点
    cout << "删除 5 后的中序遍历:" << endl;
    bst.print_inorder();

    cout << "\n=== 删除只有一个子节点的节点 ===" << endl;
    bst.remove(15); // 只有左孩子或右孩子
    cout << "删除 15 后的中序遍历:" << endl;
    bst.print_inorder();

    cout << "\n=== 删除有两个子节点的节点 ===" << endl;
    bst.remove(10); // 有两个孩子
    cout << "删除 10 后的中序遍历:" << endl;
    bst.print_inorder();

    cout << "\n=== 连续删除多个节点 ===" << endl;
    vector<int> values_to_remove = {20, 30, 25, 35};
    for (int val : values_to_remove) {
        cout << "删除 " << val << endl;
        bst.remove(val);
        bst.print_inorder();
    }

    cout << "\n=== 最终树结构 ===" << endl;
    bst.print_inorder();

    cout << "\n测试完成。" << endl;
    return 0;
}