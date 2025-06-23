#include <cstdio>

int main() {
    int n, cnt, start, end;
    scanf("%d", &n);
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
    scanf("%d", &cnt);
    
    for (int j = 0; j < cnt; ++j) {
        scanf("%d %d", &start, &end);
        --start;
        --end;
        int* temp = new int[end - start + 1];
        for (int i = start; i <= end; ++i) temp[i - start] = arr[i];
        for (int i = 0; i < end - start + 1; ++i) arr[end - i] = temp[i];
        delete[] temp;
    }

    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
    delete[] arr;
    return 0;
}