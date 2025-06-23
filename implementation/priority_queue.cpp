#include <iostream>
#include <vector>
using namespace std;

class priority_queue { // min heap
public:
    vector<int> data;
    int _size = 0;

    void heapify_up(int idx) {
        while (idx > 0) {
            if (data[idx] >= data[(idx - 1) / 2]) return;
            swap(data[idx], data[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    void heapify_down(int idx) {
        while (2 * idx + 1 < _size) {
            int child = 2 * idx + 1;
            if (child + 1 < _size && data[child] > data[child + 1]) ++child;
            if (data[idx] <= data[child]) return;
            swap(data[idx], data[child]);
            idx = child;
        }
    }

public:
    priority_queue(const vector<int>& v) : data(v), _size(v.size()) {
        for (int i = _size / 2 - 1; i >= 0; --i) heapify_down(i);
    }

    int top() { return data[0]; }

    void pop() {
        data[0] = data[--_size];
        heapify_down(0);
    }

    void push(int val) {
        data[_size++] = val;
        heapify_up(_size - 1);
    }
    
    bool empty() { return _size == 0; }

    int size() { return _size; }
};

int main() {
    // 用初始化列表直接建堆
    vector<int> elements = {7, 3, 9, 1, 4, 8};
    priority_queue pq(elements);

    cout << "Initial elements (in ascending order):" << endl;
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    // 再单独测试 push 操作
    pq.push(6);
    pq.push(2);
    pq.push(5);

    cout << "After pushing 6, 2, 5:" << endl;
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    return 0;
}
