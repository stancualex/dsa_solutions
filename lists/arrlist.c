#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int cap;
    int len;
    int *arr;
} ArrList;

ArrList init() {
    ArrList list;
    list.cap = 10;
    list.len = 0;
    list.arr = malloc(list.cap * sizeof(int));
    return list;
}

void push(ArrList *list, int key) {
    if (list->len == list->cap) {
        list->cap *= 2;
        list->arr = realloc(list->arr, list->cap * sizeof(int));
    }

    list->arr[list->len++] = key;
}

int pop(ArrList *list) {
    if (list->len == 0)
        return -1;

    return list->arr[--list->len];
}

void print(ArrList list) {
    for (int i = 0; i < list.len; ++i)
        printf("%d ", list.arr[i]);
    printf("\n");
}

int main() {
    ArrList list = init();
    for (int i = 0; i < 20; ++i)
        push(&list, i);

    print(list);
    printf("len: %d\n", list.len);

    for (int i = 0; i < 21; ++i)
        printf("%d ", pop(&list));
    printf("\n");
    printf("len: %d\n", list.len);

    free(list.arr);
    return 0;
}
