#include <stdio.h>

int binary_search(int *arr, int lo, int hi, int number) {
    if (lo > hi)
        return -1;

    int mid = (lo + hi) / 2;

    if (arr[mid] == number) {
        return mid;
    } else if (arr[mid] < number) {
        return binary_search(arr, mid + 1, hi, number);
    } else {
        return binary_search(arr, lo, mid - 1, number);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", binary_search(arr, 0, len - 1, 6));

    return 0;
}
