#include <iostream>
#include <queue>
using namespace std;

template <class T>
class Queue {
    T* data;
    int max_size;
    int front, rear;
    void DoubleSpace() {
        T* ndata = new T[max_size * 2];
        int i = 0;
        while ((front + i) % max_size != rear) {
            ndata[i + 1] = data[(front + 1 + i) % max_size];
            ++i;
        }
        delete[] data;
        data = ndata;
        front = 0;
        rear = i;
        max_size *= 2;
    }

public:
    Queue(int max = 99) : max_size(max), front(0), rear(0) {data = new T[max_size];}

    ~Queue() {delete[] data;}

    bool IsEmpty() {return front == rear;}

    void enQueue(const T& obj) {
        if ((rear + 1) % max_size == front) DoubleSpace();
        rear = (rear + 1) % max_size;
        data[rear] = obj;
    }

    T deQueue() {
        front = (front + 1) % max_size;
        return data[front];
    }

    T GetHead() {return data[(front + 1) % max_size];}
};

int main() {
    Queue<int> q(3); // 初始化容量为3

    // 测试入队
    cout << "Enqueue 1, 2, 3" << endl;
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);

    cout << "Front element: " << q.GetHead() << endl;

    // 测试出队
    cout << "Dequeue: " << q.deQueue() << endl;
    cout << "Dequeue: " << q.deQueue() << endl;

    // 测试扩容
    cout << "Enqueue 4, 5, 6, 7, 8" << endl;
    q.enQueue(4);
    q.enQueue(5);
    q.enQueue(6);
    q.enQueue(7);
    q.enQueue(8);

    cout << "Front element after several enqueues: " << q.GetHead() << endl;

    // 持续出队
    while (!q.IsEmpty()) {
        cout << "Dequeue: " << q.deQueue() << endl;
    }

    return 0;

    // Correct Output
    // Enqueue 1, 2, 3
    // Front element: 1
    // Dequeue: 1
    // Dequeue: 2
    // Enqueue 4, 5, 6, 7, 8
    // Front element after several enqueues: 3
    // Dequeue: 3
    // Dequeue: 4
    // Dequeue: 5
    // Dequeue: 6
    // Dequeue: 7
    // Dequeue: 8
}