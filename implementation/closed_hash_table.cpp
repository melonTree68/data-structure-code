#include <bits/stdc++.h>
using namespace std;

class HashTable {
private:
    struct entry {
        int data;
        int state = 0; // 0 empty, 1 active, 2 deleted
    };
    vector<entry> table;
    int size;
    int (*key)(int);
    static int defaultKey(int x) { return x; }

public:
    HashTable(int length = 101, int (*f)(int) = defaultKey) : size(length), key(f), table(vector<entry>(length)) {}

    bool find(int x) {
        int initPos, pos;
        initPos = pos = key(x) % size;
        do {
            if (table[pos].state == 0) return false;
            if (table[pos].state == 1 && x == table[pos].data) return true;
            pos = (pos + 1) % size;
        } while (pos != initPos);
        return false;
    }

    bool insert(int x) {
        int initPos, pos;
        initPos = pos = key(x) % size;
        do {
            if (table[pos].state == 1 && x == table[pos].data) return true;
            if (table[pos].state != 1) {
                table[pos].data = x;
                table[pos].state = 1;
                return true;
            }
            pos = (pos + 1) % size;
        } while (pos != initPos);
        return false;
    }

    void remove(int x) {
        int initPos, pos;
        initPos = pos = key(x) % size;
        do {
            if (table[pos].state == 0) return;
            if (table[pos].state == 1 && x == table[pos].data) {
                table[pos].state = 2;
                return;
            }
            pos = (pos + 1) % size;
        } while (pos != initPos);
    }
};

// 辅助函数，用于打印测试结果
void printTestResult(bool success, const string& testName) {
    cout << (success ? "[ PASS ] " : "[ FAIL ] ") << testName << endl;
}

// 一个自定义的哈希函数，用于测试构造函数
int customHash(int x) {
    // 一个简单的哈希，将所有数字映射到 0-9
    return (x * 7) % 10;
}

// ===============================================================
// 复杂的 main 函数
// ===============================================================

int main() {
    cout << "===== HashTable Comprehensive Test Suite =====" << endl << endl;

    // --- Test Case 1: Basic Insertion and Find ---
    cout << "--- Test Case 1: Basic Insertion and Find ---" << endl;
    {
        HashTable ht(10);
        ht.insert(5);
        ht.insert(8);
        printTestResult(ht.find(5), "Find existing element 5");
        printTestResult(ht.find(8), "Find existing element 8");
        printTestResult(!ht.find(10), "Find non-existent element 10");
        ht.insert(15); // 冲突: 15 % 10 = 5, 应该被放到下一个位置
        printTestResult(ht.find(15), "Find element 15 after collision");
    }
    cout << endl;

    // --- Test Case 2: Deletion Logic ---
    cout << "--- Test Case 2: Deletion Logic ---" << endl;
    {
        HashTable ht(10);
        ht.insert(2);
        ht.insert(12); // Collides with 2, goes to index 3
        ht.insert(22); // Collides with 2, 12, goes to index 4
        
        cout << "Before removal: find(22) should be true." << endl;
        printTestResult(ht.find(22), "Find 22 in collision chain");

        ht.remove(12); // Remove the middle element of the chain
        cout << "After removing 12:" << endl;
        printTestResult(!ht.find(12), "Find removed element 12 (should be false)");
        printTestResult(ht.find(2), "Find element 2 before deleted slot");
        printTestResult(ht.find(22), "Find element 22 after deleted slot (CRITICAL test)");
    }
    cout << endl;

    // --- Test Case 3: Re-insertion into Deleted Slots ---
    cout << "--- Test Case 3: Re-insertion into Deleted Slots ---" << endl;
    {
        HashTable ht(10);
        ht.insert(7);
        ht.insert(17); // pos 8
        ht.remove(7);  // pos 7 is now 'deleted'
        printTestResult(!ht.find(7), "Confirm 7 is removed");
        
        bool inserted = ht.insert(27); // pos 7, should reuse the deleted slot
        printTestResult(inserted, "Insert 27 into a deleted slot");
        printTestResult(ht.find(27), "Find 27 in its new (reused) slot");
        printTestResult(ht.find(17), "Find 17 to ensure chain is not broken");
    }
    cout << endl;

    // --- Test Case 4: Full Table ---
    cout << "--- Test Case 4: Full Table ---" << endl;
    {
        HashTable ht(5);
        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        ht.insert(4);
        ht.insert(5);

        printTestResult(ht.find(3), "Find element in a full table");
        printTestResult(!ht.insert(6), "Attempt to insert into a full table (should fail)");
        ht.remove(3);
        printTestResult(ht.insert(6), "Insert after making space in a full table");
        printTestResult(ht.find(6), "Find newly inserted element 6");
    }
    cout << endl;

    // --- Test Case 5: Custom Hash Function ---
    cout << "--- Test Case 5: Custom Hash Function ---" << endl;
    {
        HashTable ht(10, customHash); // Use customHash: (x*7)%10
        // 15 -> (15*7)%10 = 105%10 = 5
        // 25 -> (25*7)%10 = 175%10 = 5 (collision)
        // 3 ->  (3*7)%10  = 21%10  = 1
        ht.insert(15);
        ht.insert(25);
        ht.insert(3);

        printTestResult(ht.find(15), "Custom Hash: Find 15 (at pos 5)");
        printTestResult(ht.find(25), "Custom Hash: Find 25 (at pos 6)");
        printTestResult(ht.find(3), "Custom Hash: Find 3 (at pos 1)");
        printTestResult(!ht.find(5), "Custom Hash: Find non-existent 5");
    }
    cout << endl;

    // --- Test Case 6: Large-Scale Stress Test ---
    cout << "--- Test Case 6: Large-Scale Stress Test ---" << endl;
    {
        const int TABLE_SIZE = 997; // A prime number
        const int NUM_TO_INSERT = 800;
        const int NUM_TO_REMOVE = 400;

        HashTable ht(TABLE_SIZE);
        vector<int> all_numbers(NUM_TO_INSERT);
        std::iota(all_numbers.begin(), all_numbers.end(), 1); // Fill with 1, 2, ..., 800

        // Use a random engine for shuffling
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(all_numbers.begin(), all_numbers.end(), g);

        set<int> inserted_numbers;
        set<int> removed_numbers;

        // Insert phase
        for (int i = 0; i < NUM_TO_INSERT; ++i) {
            ht.insert(all_numbers[i]);
            inserted_numbers.insert(all_numbers[i]);
        }
        cout << "Inserted " << NUM_TO_INSERT << " random numbers." << endl;

        // Remove phase
        for (int i = 0; i < NUM_TO_REMOVE; ++i) {
            ht.remove(all_numbers[i]);
            inserted_numbers.erase(all_numbers[i]);
            removed_numbers.insert(all_numbers[i]);
        }
        cout << "Removed " << NUM_TO_REMOVE << " of them." << endl;

        // Verification phase
        bool all_found = true;
        for (int num : inserted_numbers) {
            if (!ht.find(num)) {
                all_found = false;
                cout << "Error: Should have found " << num << " but did not." << endl;
                break;
            }
        }
        printTestResult(all_found, "Stress Test: Verify all remaining elements are found");

        bool all_removed = true;
        for (int num : removed_numbers) {
            if (ht.find(num)) {
                all_removed = false;
                cout << "Error: Should not have found " << num << " but did." << endl;
                break;
            }
        }
        printTestResult(all_removed, "Stress Test: Verify all removed elements are not found");
        
        printTestResult(!ht.find(9999), "Stress Test: Verify a completely new number is not found");
    }
    cout << endl;

    cout << "===== Test Suite Finished =====" << endl;
    return 0;
}