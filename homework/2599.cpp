#include <cstdio>

struct Node {
    int val;
    Node* next;
    Node(int v, Node* n = nullptr) : val(v), next(n) {}
    Node(Node* n = nullptr) : next(n) {}
};

int main() {
    int n, val;
    scanf("%d", &n);
    Node* head = new Node;
    Node* itr = head;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &val);
        itr->next = new Node(val);
        itr = itr->next;
    }

    scanf("%d", &n);
    // head = head->next;
    itr = head;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &val);
        while (itr->next && itr->next->val < val) itr = itr->next; 
        Node* temp = new Node(val, itr->next);
        itr->next = temp;
        itr = temp;
    }

    head = head->next;
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }

    return 0;
}