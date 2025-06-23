#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) return;
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int val = arr[i];
        int j = i;
        for (; j > 0 && arr[j - 1] > val; --j) arr[j] = arr[j - 1];
        arr[j] = val;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        int minIdx = i;
        for (int j = i; j < n; ++j) if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

void shellSort(vector<int>& arr) {
    int n = arr.size();
    int gap = 1;
    while (gap < n / 3) gap = 3 * gap + 1;
    for (; gap > 0; gap /= 3) {
        for (int i = gap; i < n; ++i) { 
            int val = arr[i];
            int j = i;
            for (; j >= gap && arr[j - gap] > val; j -= gap) arr[j] = arr[j - gap];
            arr[j] = val;
        }
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> data(arr.begin() + left, arr.begin() + right + 1);
    int i = 0, j = mid + 1 - left, k = left;
    while (i <= mid - left && j <= right - left) arr[k++] = data[i] <= data[j] ? data[i++] : data[j++];
    while (i <= mid - left) arr[k++] = data[i++];
    while (j <= right - left) arr[k++] = data[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }

int partition(vector<int>& arr, int low, int high) {
    int val = arr[high];
    int i = low, pos = low;
    for (; i < high; ++i) if (arr[i] < val) swap(arr[i], arr[pos++]);
    swap(arr[pos], arr[high]);
    return pos;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int pivot = partition(arr, low, high);
    quickSort(arr, low, pivot - 1);
    quickSort(arr, pivot + 1, high);
}

void quickSort(vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }

void heapSort(vector<int>& arr) {
    priority_queue<int, vector<int>, greater<int>> pq(arr.begin(), arr.end());
    int i = 0;
    while (!pq.empty()) {
        arr[i++] = pq.top();
        pq.pop();
    }
}

// ===================================================================
// 测试框架
// ===================================================================

// 定义函数指针类型，让代码更清晰
using SortFuncPtr = void (*)(std::vector<int>&);

// 定义一个结构体来关联算法名称和它的函数指针
struct Algorithm {
    std::string name;
    SortFuncPtr func;
};

// ANSI 颜色代码，用于美化输出
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// 运行单个测试的核心函数
void runTest(const Algorithm& algo, const std::string& testName, std::vector<int> testData) {
    // 复制一份数据，用于和 std::sort 的结果进行比较
    std::vector<int> expected = testData;
    std::sort(expected.begin(), expected.end());

    // 计时开始
    auto start = std::chrono::high_resolution_clock::now();
    
    // 通过函数指针调用你的排序算法
    algo.func(testData);

    // 计时结束
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    // 验证结果
    if (testData == expected) {
        printf(ANSI_COLOR_GREEN "[ PASS ]" ANSI_COLOR_RESET " %-16s on %-35s (%.4f ms)\n",
               algo.name.c_str(), testName.c_str(), duration.count());
    } else {
        printf(ANSI_COLOR_RED "[ FAIL ]" ANSI_COLOR_RESET " %-16s on %-35s (%.4f ms)\n",
               algo.name.c_str(), testName.c_str(), duration.count());
        
        // 如果失败，可以取消下面的注释来查看详细的错误信息
        // std::cout << "         Expected: "; for(int i : expected) std::cout << i << " "; std::cout << std::endl;
        // std::cout << "         Got:      "; for(int i : testData) std::cout << i << " "; std::cout << std::endl;
    }
}


// ===================================================================
// 主函数
// ===================================================================
int main() {
    // -----------------------------------------------------------------
    // 1. 在这里定义你的函数指针数组
    //    你只需要在这里添加或删除算法即可
    // -----------------------------------------------------------------
    Algorithm algorithms_to_test[] = {
        {"Bubble Sort",    bubbleSort},
        {"Insertion Sort", insertionSort},
        {"Selection Sort", selectionSort},
        {"Shell Sort",     shellSort},
        {"Merge Sort",     mergeSort},
        {"Quick Sort",     quickSort},
        {"Heap Sort",      heapSort},
        // {"Faulty Sort",    faultySort}
        // 如果你有更多算法，比如 shellSort，像这样添加:
        // {"Shell Sort",     shellSort}
    };

    // -----------------------------------------------------------------
    // 2. 定义一系列测试用例
    // -----------------------------------------------------------------
    std::vector<std::pair<std::string, std::vector<int>>> test_cases;
    test_cases.push_back({"Empty Vector", {}});
    test_cases.push_back({"Single Element", {100}});
    test_cases.push_back({"Already Sorted", {1, 2, 3, 4, 5, 6, 7}});
    test_cases.push_back({"Reverse Sorted", {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}});
    test_cases.push_back({"All Elements Same", {8, 8, 8, 8, 8}});
    test_cases.push_back({"Contains Duplicates", {5, 2, 9, 5, 1, 9, 2, 5}});
    test_cases.push_back({"Contains Negative Numbers", {-10, 5, -20, 0, -1, 15, 8}});

    // 创建大规模随机数据
    std::vector<int> large_random;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distrib(-5000, 5000);
    for (int i = 0; i < 5000; ++i) {
        large_random.push_back(distrib(gen));
    }
    test_cases.push_back({"Large Random Data (5000 elements)", large_random});

    // -----------------------------------------------------------------
    // 3. 运行测试
    // -----------------------------------------------------------------
    std::cout << ANSI_COLOR_CYAN "=============================================" << std::endl;
    std::cout << "     Running Sorting Algorithm Test Suite" << std::endl;
    std::cout << "=============================================" ANSI_COLOR_RESET << std::endl << std::endl;
    
    // 使用 C-style 数组的遍历方式
    for (const auto& algo : algorithms_to_test) {
        std::cout << ANSI_COLOR_YELLOW "--- Testing: " << algo.name << " ---" ANSI_COLOR_RESET << std::endl;
        for (const auto& test_case : test_cases) {
            runTest(algo, test_case.first, test_case.second);
        }
        std::cout << std::endl;
    }

    std::cout << ANSI_COLOR_CYAN "=============================================" << std::endl;
    std::cout << "           All tests completed." << std::endl;
    std::cout << "=============================================" ANSI_COLOR_RESET << std::endl;

    return 0;
}