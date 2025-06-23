#include <iostream>
using namespace std;

template <class T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* n = nullptr) : data(data), next(n) {}
        Node(Node* n = nullptr) : next(n) {}
    };
    Node* top_p;

public:
    Stack() : top_p(nullptr) {}

    ~Stack() {
        Node* temp;
        while (top_p) {
            temp = top_p;
            top_p = top_p->next;
            delete temp;
        }
    }
    
    bool isEmpty() { return top_p; }

    void push(const T& obj) { top_p = new Node(obj, top_p); }

    T pop() {
        Node* temp = top_p;
        top_p = top_p->next;
        T res = temp->data;
        delete temp;
        return res;
    }

    T top() const { return top_p->data; }
};

// int main() {
//     // 创建一个栈
//     Stack<int> stack;

//     // 测试 Push 操作
//     stack.push(10);
//     stack.push(20);
//     stack.push(30);

//     // 输出栈顶元素
//     cout << "Top element: " << stack.top() << endl;  // 应该输出 30

//     // 测试 pop 操作
//     cout << "Popped element: " << stack.pop() << endl;  // 应该输出 30
//     cout << "Popped element: " << stack.pop() << endl;  // 应该输出 20

//     // 输出栈顶元素
//     cout << "Top element after popping: " << stack.top() << endl;  // 应该输出 10

//     // 测试栈是否为空
//     if (stack.isEmpty()) {
//         cout << "Stack is empty." << endl;
//     } else {
//         cout << "Stack is not empty." << endl;
//     }

//     // 输出栈顶元素
//     cout << "Popped element: " << stack.pop() << endl;  // 应该输出 10

//     // 测试栈是否为空
//     if (stack.isEmpty()) {
//         cout << "Stack is empty." << endl;
//     } else {
//         cout << "Stack is not empty." << endl;
//     }

//     return 0;
// }