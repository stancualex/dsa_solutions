#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cap;
    int size;
    float *arr;
} ArrList;

void init(ArrList *list) {
    list->cap = 6;
    list->size = 0;
    list->arr = malloc(list->cap * sizeof(float));
}

void insert_last(ArrList *list, float val) {
    if (list->size == list->cap) {
        (list->cap) *= 2;
        list->arr = realloc(list->arr, list->cap * sizeof(float));
    }

    list->arr[list->size] = val;
    (list->size)++;
}

void insert_first(ArrList *list, float val) {
    if (list->size == list->cap) {
        (list->cap) *= 2;
        list->arr = realloc(list->arr, list->cap * sizeof(float));
    }

    for (int i = list->size; i >= 0; --i)
        list->arr[i] = list->arr[i - 1];
    list->arr[0] = val;
    (list->size)++;
}

void print_arrlist(ArrList *list) {
    for (int i = 0; i < list->size; ++i)
        printf("%.2f ", list->arr[i]);
    printf("\n");
}

void print_steps(ArrList *list, void (*func)(ArrList *, float)) {
    for (int i = 1; i <= 10; ++i) {
        func(list, (float) i);
        print_arrlist(list);
    }
    printf("\n");
}

int main() {
    ArrList arr;
    init(&arr);
    print_steps(&arr, insert_first);
    init(&arr);
    print_steps(&arr, insert_last);

    return 0;
}
