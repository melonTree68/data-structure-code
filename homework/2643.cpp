#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<char> s;
    char ch;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> ch;
        if (ch == '(' || ch == '[' || ch == '{') s.push(ch);
        else if (ch == ')') {
            if (s.empty() || s.top() != '(') {
                cout << 0;
                return 0;
            }
            else s.pop();
        }
        else if (ch == ']') {
            if (s.empty() || s.top() != '[') {
                cout << 0;
                return 0;
            }
            else s.pop();
        }
        else if (ch == '}') {
            if (s.empty() || s.top() != '{') {
                cout << 0;
                return 0;
            }
            else s.pop();
        }
    }
    cout << s.empty();
    return 0;
}