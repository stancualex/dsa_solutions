#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next, *prev;
} NodeT;

typedef struct list {
    int len;
    NodeT *head, *tail;
} LinkedList;

NodeT *create(int key) {
    NodeT *p = malloc(sizeof(NodeT));
    p->key = key;
    p->next = p->prev = NULL;
    return p;
}

LinkedList init() {
    LinkedList list;
    list.len = 0;
    list.head = list.tail = NULL;
    return list;
}

void prepend(LinkedList *list, int key) {
    NodeT *p = create(key);
    list->len++;
    if (list->head == NULL) {
        list->head = list->tail = p;
        return;
    }

    p->next = list->head;
    list->head->prev = p;
    list->head = p;
}

void append(LinkedList *list, int key) {
    NodeT *p = create(key);
    list->len++;
    if (list->head == NULL) {
        list->head = list->tail = p;
        return;
    }

    list->tail->next = p;
    p->prev = list->tail;
    list->tail = p;
}

void insert_at(LinkedList *list, int idx, int key) {
    if (idx > list->len || idx < 0) {
        return;
    } else if (idx == list->len) {
        append(list, key);
        return;
    } else if (idx == 0) {
        prepend(list, key);
        return;
    }

    list->len++;
    NodeT *curr = list->head;
    for (int i = 0; i < idx; ++i)
        curr = curr->next;
    NodeT *p = create(key);
    p->next = curr;
    p->prev = curr->prev;
    curr->prev->next = p;
    curr->prev = p;
}

int del_first(LinkedList *list) {
    if (list->head == NULL)
        return -1;

    list->len--;
    NodeT *p = list->head;
    int key = p->key;
    if (list->len == 0) {
        list->head = list->tail = NULL;
        return key;
    }
    list->head = p->next;
    list->head->prev = NULL;
    free(p);

    return key;
}

int del_last(LinkedList *list) {
    if (list->tail == NULL)
        return -1;

    list->len--;
    NodeT *p = list->tail;
    int key = p->key;
    if (list->len == 0) {
        list->head = list->tail = NULL;
        return key;
    }
    list->tail = p->prev;
    list->tail->next = NULL;
    free(p);

    return key;
}

int del_key(LinkedList *list, int key) {
    NodeT *curr = list->head;
    int idx = 0;
    for (; idx < list->len; ++idx, curr = curr->next)
        if (curr->key == key)
            break;

    if (curr == NULL) {
        return -1;
    } else if (curr->prev == NULL) {
        del_first(list);
        return idx;
    } else if (curr->next == NULL) {
        del_last(list);
        return idx;
    }

    list->len--;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    free(curr);

    return idx;
}

int del_at(LinkedList *list, int idx) {
    if (idx >= list->len || idx < 0) {
        return -1;
    } else if (idx == list->len - 1) {
        return del_last(list);
    } else if (idx == 0) {
        return del_first(list);
    }

    list->len--;
    NodeT *curr = list->head;
    for (int i = 0; i < idx; ++i)
        curr = curr->next;

    int key = curr->key;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    free(curr);

    return key;
}

int get_key(LinkedList list, int key) {
    NodeT *curr = list.head;
    int idx = 0;
    for (; idx < list.len; ++idx, curr = curr->next)
        if (curr->key == key)
            break;

    if (curr == NULL)
        return -1;

    return idx;
}

int get_at(LinkedList list, int idx) {
    if (idx >= list.len || idx < 0)
        return -1;

    NodeT *curr = list.head;
    for (int i = 0; i < idx; ++i)
        curr = curr->next;

    return curr->key;
}

void drop(LinkedList *list) {
    while (list->head != NULL) {
        NodeT *p = list->head;
        list->head = list->head->next;
        free(p);
    }
    list->tail = NULL;
}

void print_list(LinkedList list) {
    for (NodeT *p = list.head; p != NULL; p = p->next)
        printf("%d ", p->key);
    printf("\n");
}

void print_list_rev(LinkedList list) {
    for (NodeT *p = list.tail; p != NULL; p = p->prev)
        printf("%d ", p->key);
    printf("\n");
}

int main() {
    LinkedList list = init();
    for (int i = 0; i < 5; ++i)
        prepend(&list, i);
    for (int i = 0; i < 5; ++i)
        append(&list, i);

    insert_at(&list, 5, 5);
    insert_at(&list, 0, 11);

    // for (int i = 0; i < 12; ++i)
    //     printf("%d ", del_last(&list));
    // printf("\n");

    printf("%d\n", del_key(&list, 3));
    printf("%d\n", del_key(&list, 4));
    printf("%d\n", del_key(&list, 3));
    printf("%d\n", get_at(list, -1));
    printf("%d\n", get_at(list, 1));
    printf("%d\n", get_key(list, 0));
    printf("%d\n", del_at(&list, 0));
    printf("%d\n", del_at(&list, 2));

    print_list(list);
    print_list_rev(list);
    printf("length: %d\n", list.len);

    drop(&list);
    return 0;
}
