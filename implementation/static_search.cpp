#include <bits/stdc++.h>
using namespace std;

int binarySearch(const vector<int>& data, int x) {
    int low = 0, high = data.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (x == data[mid]) return mid;
        if (x < data[mid]) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

int interpolationSearch(const vector<int>& data, int x) {
    int low = 0, high = data.size() - 1;
    while (low <= high && x >= data[low] && x <= data[high]) {
        if (data[low] == data[high]) return x == data[low] ? low : -1;
        int pos = low + (high - low) * (x - data[low]) / (data[high] - data[low]);
        if (x == data[pos]) return pos;
        if (x < data[pos]) high = pos - 1;
        else low = pos + 1;
    }
    return -1;
}

int main() {
    // 准备一个标准的、分布均匀的测试数组
    vector<int> data = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    cout << "--- Test 1: Find an element in the middle ---" << endl;
    cout << "Binary Search for 70: " << binarySearch(data, 70) << endl;
    // Expected: 6 (因为 70 在数组的第7个位置，索引为6)
    cout << "Interpolation Search for 70: " << interpolationSearch(data, 70) << endl;
    // Expected: 6
    cout << "------------------------------------------" << endl;

    cout << "--- Test 2: Find the first element ---" << endl;
    cout << "Binary Search for 10: " << binarySearch(data, 10) << endl;
    // Expected: 0
    cout << "Interpolation Search for 10: " << interpolationSearch(data, 10) << endl;
    // Expected: 0
    cout << "------------------------------------------" << endl;

    cout << "--- Test 3: Find the last element ---" << endl;
    cout << "Binary Search for 100: " << binarySearch(data, 100) << endl;
    // Expected: 9
    cout << "Interpolation Search for 100: " << interpolationSearch(data, 100) << endl;
    // Expected: 9
    cout << "------------------------------------------" << endl;

    cout << "--- Test 4: Element not found (in range) ---" << endl;
    cout << "Binary Search for 55: " << binarySearch(data, 55) << endl;
    // Expected: -1 (未找到)
    cout << "Interpolation Search for 55: " << interpolationSearch(data, 55) << endl;
    // Expected: -1
    cout << "------------------------------------------" << endl;

    cout << "--- Test 5: Element not found (out of range) ---" << endl;
    cout << "Binary Search for 110: " << binarySearch(data, 110) << endl;
    // Expected: -1
    cout << "Interpolation Search for 110: " << interpolationSearch(data, 110) << endl;
    // Expected: -1 (会因为 while 条件不满足而直接返回-1，非常安全)
    cout << "------------------------------------------" << endl;
    
    cout << "--- Test 6: Empty vector ---" << endl;
    vector<int> empty_data = {};
    cout << "Binary Search in empty: " << binarySearch(empty_data, 10) << endl;
    // Expected: -1
    cout << "Interpolation Search in empty: " << interpolationSearch(empty_data, 10) << endl;
    // Expected: -1 (函数开头的检查会处理这种情况)
    cout << "------------------------------------------" << endl;

    return 0;
}