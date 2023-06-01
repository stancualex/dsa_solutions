#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100000

void merge_default(int *arr, int lo, int hi) {
    int mid = (lo + hi) / 2;

    int idx_lo = lo, idx_hi = mid + 1, idx_arr = 0;
    int temp_arr[hi - lo + 1];

    while (idx_lo <= mid && idx_hi <= hi) {
        if (arr[idx_lo] < arr[idx_hi]) {
            temp_arr[idx_arr++] = arr[idx_lo++];
        } else {
            temp_arr[idx_arr++] = arr[idx_hi++];
        }
    }

    while (idx_lo <= mid)
        temp_arr[idx_arr++] = arr[idx_lo++];

    while (idx_hi <= hi)
        temp_arr[idx_arr++] = arr[idx_hi++];

    memcpy(arr + lo, temp_arr, sizeof(temp_arr));
}

void merge_sort_default(int *arr, int lo, int hi) {
    if (lo >= hi)
        return;

    int mid = (lo + hi) / 2;

    merge_sort_default(arr, lo, mid);
    merge_sort_default(arr, mid + 1, hi);

    merge_default(arr, lo, hi);
}

int *merge2(int *left, int len_left, int *right, int len_right) {
    int *arr = malloc((len_left + len_right) * sizeof(int));
    int idx_left = 0, idx_right = 0, idx_arr = 0;

    while (idx_left < len_left && idx_right < len_right) {
        if (left[idx_left] < right[idx_right]) {
            arr[idx_arr++] = left[idx_left++];
        } else {
            arr[idx_arr++] = right[idx_right++];
        }
    }

    while (idx_left < len_left)
        arr[idx_arr++] = left[idx_left++];

    while (idx_right < len_right)
        arr[idx_arr++] = right[idx_right++];

    return arr;
}

int *mergesort2(int *arr, int len) {
    if (len <= 1)
        return arr;

    int len_left = len / 2;
    int len_right = len - len_left;

    int *left = mergesort2(arr, len_left);
    int *right = mergesort2(arr + len_left, len_right);

    return merge2(left, len_left, right, len_right);
}

int *merge3(int *left, int len_left, int *mid, int len_mid, int *right, int len_right) {
    int *arr = malloc((len_left + len_mid + len_right) * sizeof(int));
    int idx_left = 0, idx_mid = 0, idx_right = 0, idx_arr = 0;

    while (idx_left < len_left && idx_mid < len_mid && idx_right < len_right) {
        if (left[idx_left] < mid[idx_mid]) {
            if (left[idx_left] < right[idx_right]) {
                arr[idx_arr++] = left[idx_left++];
            } else {
                arr[idx_arr++] = right[idx_right++];
            }
        } else {
            if (mid[idx_mid] < right[idx_right]) {
                arr[idx_arr++] = mid[idx_mid++];
            } else {
                arr[idx_arr++] = right[idx_right++];
            }
        }
    }

    while (idx_left < len_left && idx_mid < len_mid) {
        if (left[idx_left] < mid[idx_mid]) {
            arr[idx_arr++] = left[idx_left++];
        } else {
            arr[idx_arr++] = mid[idx_mid++];
        }
    }

    while (idx_left < len_left && idx_right < len_right) {
        if (left[idx_left] < right[idx_right]) {
            arr[idx_arr++] = left[idx_left++];
        } else {
            arr[idx_arr++] = right[idx_right++];
        }
    }

    while (idx_mid < len_mid && idx_right < len_right) {
        if (mid[idx_mid] < right[idx_right]) {
            arr[idx_arr++] = mid[idx_mid++];
        } else {
            arr[idx_arr++] = right[idx_right++];
        }
    }

    while (idx_left < len_left)
        arr[idx_arr++] = left[idx_left++];

    while (idx_mid < len_mid)
        arr[idx_arr++] = mid[idx_mid++];

    while (idx_right < len_right)
        arr[idx_arr++] = right[idx_right++];

    return arr;
}

int *mergesort3(int *arr, int len) {
    if (len <= 1)
        return arr;

    int len_left = len / 3;
    int len_mid = (len - len_left) / 2;
    int len_right = len - len_left - len_mid;

    int *left = mergesort3(arr, len_left);
    int *mid = mergesort3(arr + len_left, len_mid);
    int *right = mergesort3(arr + len_left + len_mid, len_right);

    return merge3(left, len_left, mid, len_mid, right, len_right);
}

int partition(int *arr, int lo, int hi) {
    int pivot = arr[(lo + hi) / 2];
    int idx_lo = lo, idx_hi = hi;

    while (idx_lo <= idx_hi) {
        while (arr[idx_lo] < pivot)
            idx_lo++;
        while (arr[idx_hi] > pivot)
            idx_hi--;
        if (idx_lo <= idx_hi) {
            int aux = arr[idx_lo];
            arr[idx_lo++] = arr[idx_hi];
            arr[idx_hi--] = aux;
        }
    }

    return idx_lo;
}

void quick_sort(int *arr, int lo, int hi) {
    if (lo >= hi)
        return;

    int pivot_idx = partition(arr, lo, hi);

    if (lo < pivot_idx - 1)
        quick_sort(arr, lo, pivot_idx - 1);
    if (pivot_idx < hi)
        quick_sort(arr, pivot_idx, hi);
}

int main() {
    int arr[LEN];
    for (int i = 0, j = LEN - 1; i < LEN; i++, j--)
        arr[i] = j;

    merge_sort_default(arr, 0, LEN - 1);
    // quick_sort(arr, 0, LEN - 1);
    for (int i = 0; i < LEN; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    // int *sorted2 = mergesort2(arr, LEN);
    // for (int i = 0; i < LEN; ++i)
    //     printf("%d ", sorted2[i]);
    // printf("\n");
    //
    // int *sorted3 = mergesort3(arr, LEN);
    // for (int i = 0; i < LEN; ++i)
    //     printf("%d ", sorted3[i]);
    // printf("\n");

    // free(sorted2);
    // free(sorted3);
    return 0;
}
