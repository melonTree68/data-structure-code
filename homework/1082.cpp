#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    vector<int> a;
    list<int> min, max; // store index
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        a.push_back(tmp);
    }

    for (int i = 0; i < n; ++i) { // i is the greatest index in the window
        // maintain min
        while (!min.empty() && a[min.back()] >= a[i]) min.pop_back();
        while (!min.empty() && min.front() <= i - k) min.pop_front();
        min.push_back(i);
        if (i >= k - 1) cout << a[min.front()] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) { // i is the greatest index in the window
        // maintain max
        while (!max.empty() && a[max.back()] <= a[i]) max.pop_back();
        while (!max.empty() && max.front() <= i - k) max.pop_front();
        max.push_back(i);
        if (i >= k - 1) cout << a[max.front()] << " ";
    }
    
    return 0;
}