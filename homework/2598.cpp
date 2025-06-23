#include <stdio.h>

int main() {
    int n, x;
    scanf("%d", &n);
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
    scanf("%d", &x);

    for (int i = 0; i < n; ++i) if (arr[i] < x) printf("%d ", arr[i]);
    for (int i = 0; i < n; ++i) if (arr[i] >= x) printf("%d ", arr[i]);
    return 0;
}