#include <iostream>
#include <stack>
using namespace std;

void BinaryOp(char op, stack<int>& out) {
    int a, b;
    a = out.top();
    out.pop();
    b = out.top();
    out.pop();
    switch (op) {
        case '+':
            out.push(a + b);
            break;
        case '*':
            out.push(a * b);
            break;
    }
}

int Calc(char* str) {
    stack<char> ops;
    stack<int> out;
    while (*str) {
        if (*str >= '0' && *str <= '9') out.push(*str - '0');
        else switch (*str) {
            case '(':
                ops.push(*str);
                break;
            case ')':
                while (!ops.empty() && ops.top() != '(') {
                    BinaryOp(ops.top(), out);
                    ops.pop();
                }
                ops.pop();
                break;
            case '+':
                while (!ops.empty() && ops.top() != '(') {
                    BinaryOp(ops.top(), out);
                    ops.pop();
                }
                ops.push(*str);
                break;
            case '*':
                while (!ops.empty() && ops.top() == '*') {
                    BinaryOp(ops.top(), out);
                    ops.pop();
                }
                ops.push(*str);
                break;
        }
        ++str;
    }

    while (!ops.empty()) {
        BinaryOp(ops.top(), out);
        ops.pop();
    }

    return out.top();
}

int main() {
    char str[100];
    cin >> str;
    cout << Calc(str);
    return 0;
}