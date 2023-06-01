#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} *NodeT;

typedef struct list {
    int len;
    NodeT head;
    NodeT tail;
} LinkedList;

NodeT create(int key) {
    NodeT p = malloc(sizeof(struct node));
    p->key = key;
    p->next = NULL;
    return p;
}

LinkedList init() {
    LinkedList list;
    list.len = 0;
    list.head = list.tail = NULL;
    return list;
}

void prepend(LinkedList *list, int key) {
    NodeT p = create(key);
    list->len++;
    if (list->head == NULL) {
        list->head = list->tail = p;
        return;
    }

    p->next = list->head;
    list->head = p;
}

void append(LinkedList *list, int key) {
    NodeT p = create(key);
    list->len++;
    if (list->head == NULL) {
        list->head = list->tail = p;
        return;
    }

    list->tail->next = p;
    list->tail = p;
}

int get_key(LinkedList list, int key) {
    NodeT curr = list.head;
    int idx = 0;
    for (; idx < list.len; ++idx, curr = curr->next)
        if (curr->key == key)
            break;

    if (curr == NULL)
        return -1;

    return idx;
}

void insert_after(LinkedList *list, int after_key, int key) {
    int idx = get_key(*list, after_key);

    if (idx == -1) {
        return;
    } else if (idx == list->len - 1) {
        append(list, key);
        return;
    }

    list->len++;
    NodeT curr = list->head;
    for (int i = 0; i < idx; ++i)
        curr = curr->next;
    NodeT p = create(key);
    p->next = curr->next;
    curr->next = p;
}

int del_first(LinkedList *list) {
    if (list->head == NULL)
        return -1;

    list->len--;
    NodeT p = list->head;
    int key = p->key;
    list->head = p->next;
    free(p);
    return key;
}

int del_last(LinkedList *list) {
    if (list->head == NULL)
        return -1;

    list->len--;
    NodeT p = list->head;
    if (list->len == 0) {
        int key = p->key;
        free(p);
        list->head = list->tail = NULL;
        return key;
    }

    int key = list->tail->key;
    while (p->next != list->tail)
        p = p->next;
    free(list->tail);
    list->tail = p;
    p->next = NULL;
    return key;
}

int del_key(LinkedList *list, int key) {
    NodeT curr = list->head;
    int idx = 0;
    for (; idx < list->len; ++idx, curr = curr->next)
        if (curr->key == key)
            break;

    if (curr == NULL) {
        return -1;
    } else if (curr == list->head) {
        del_first(list);
        return idx;
    } else if (curr->next == NULL) {
        del_last(list);
        return idx;
    }

    list->len--;
    NodeT p = list->head;
    while (p->next != curr)
        p = p->next;
    p->next = curr->next;
    free(curr);
    return idx;
}

void print(LinkedList list) {
    for (NodeT p = list.head; p != NULL; p = p->next)
        printf("%d ", p->key);
    printf("\n");
}

int main() {
    LinkedList list = init();

    for (int i = 0; i < 5; ++i)
        append(&list, i);

    print(list);
    printf("len: %d\n", list.len);

    for (int i = 5; i < 10; ++i)
        prepend(&list, i);

    print(list);
    printf("len: %d\n", list.len);

    insert_after(&list, 2, 7);
    insert_after(&list, 3, 8);
    insert_after(&list, 4, 5);

    print(list);
    printf("len: %d\n", list.len);

    del_first(&list);
    del_last(&list);
    del_key(&list, 2);

    print(list);
    printf("len: %d\n", list.len);

    for (int i = 0; i < 11; ++i)
        printf("%d ", del_first(&list));
    printf("\n");

    print(list);
    printf("len: %d\n", list.len);

    return 0;
}
