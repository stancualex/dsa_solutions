#include <stdio.h>

int binary_search(int *arr, int lo, int hi, int number) {
    // pas 2
    if (lo > hi)
        return -1;

    // pas 3
    int mid = (lo + hi) / 2;

    if (arr[mid] == number) {
        // pas 4
        return mid;
    } else if (arr[mid] < number) {
        // pas 5
        return binary_search(arr, mid + 1, hi, number);
    } else {
        // pas 6
        return binary_search(arr, lo, mid - 1, number);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", binary_search(arr, 0, len - 1, 6));

    return 0;
}

