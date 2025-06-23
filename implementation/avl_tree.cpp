#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class avl_tree {
private:
    struct Node {
        int val, height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(int v) : val(v) {}
    };

    Node* root = nullptr;

    int height(Node* r) { return r ? r->height : -1; }

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

    void LL(Node*& r) {
        auto tmp = r->left;
        r->left = tmp->right;
        tmp->right = r;
        r = tmp;
    }
    
    void RR(Node*& r) {
        auto tmp = r->right;
        r->right = tmp->left;
        tmp->left = r;
        r = tmp;
    }

    void LR(Node*& r) {
        RR(r->left);
        LL(r);
    }

    void RL(Node*& r) {
        LL(r->right);
        RR(r);
    }

    void insert(int x, Node*& r) {
        if (!r) {
            r = new Node(x);
            return;
        }
        if (x == r->val) return;

        if (x < r->val) {
            insert(x, r->left);
            if (height(r->left) - height(r->right) == 2) {
                if (height(r->left->left) > height(r->left->right)) LL(r);
                else LR(r);
            }
        }
        else {
            insert(x, r->right);
            if (height(r->left) - height(r->right) == -2) {
                if (height(r->right->left) > height(r->right->right)) RL(r);
                else RR(r);
            }
        }
        r->height = max(height(r->left), height(r->right)) + 1;
    }

    bool adjust(Node*& r, int p) {
        int bf = height(r->left) - height(r->right);
        if (p) {
            if (bf == 1) return true;
            if (bf == 0) return false;

            if (height(r->left->left) < height(r->left->right)) {
                LR(r);
                return false;
            }
            else if (height(r->left->left) == height(r->left->right)) {
                LL(r);
                return true;
            }
            else {
                LL(r);
                return false;
            }
        }
        else {
            if (bf == -1) return true;
            if (bf == 0) return false;

            if (height(r->right->left) > height(r->right->right)) {
                RL(r);
                return false;
            }
            else if (height(r->right->left) == height(r->right->right)) {
                RR(r);
                return true;
            }
            else {
                RR(r);
                return false;
            }
        }
    }

    bool remove(int x, Node*& r) {
        if (!r) return true;
        if (x == r->val) {
            if (r->left && r->right) {
                // left-most node in right subtree
                auto tmp = r->right;
                while (tmp->left) tmp = tmp->left;
                r->val = tmp->val;
                if (remove(r->val, r->right)) return true;
                else return adjust(r, 1);
            }
            else {
                auto tmp = r;
                r = r->left ? r->left : r->right;
                delete tmp;
                return false;
            }
        }
        else {
            if (x < r->val) {
                return remove(x, r->left) ? true : adjust(r, 0);
            }
            else {
                return remove(x, r->right) ? true : adjust(r, 1);
            }
        }
    }

public:
    ~avl_tree() { del(root); }

    void print_inorder() {
        if (!root) return;
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

    bool find(int x) { return find(x, root); }

    void insert(int x) { insert(x, root); }

    void remove(int x) { remove(x, root); }
};

int main() {
    avl_tree tree;

    vector<int> values_to_insert = {1, 3, 6, 4, 2, 5, 7};
    for (int val : values_to_insert) {
        tree.insert(val);
    }

    cout << "In-order after insertions: ";
    tree.print_inorder();

    for (int x : {4, 6, 8}) {
        cout << "Find " << x << ": " << (tree.find(x) ? "Yes" : "No") << endl;
    }

    vector<int> values_to_remove = {3, 4, 2, 0, 8};
    for (int val : values_to_remove) {
        tree.remove(val);
        cout << "In-order after removing " << val << ": ";
        tree.print_inorder();
    }

    return 0;
}
