#include <stdio.h>
#include <stdlib.h>

#define M 7

typedef struct node {
    int key;
    struct node *next;
} NodeT;

int h_func(int key) {
    key %= M;
    if (key < 0)
        key += M;
    return key;
}

void insert_elem(NodeT *hTable[M], int key) {
    int h = h_func(key);
    NodeT *p = malloc(sizeof(NodeT));
    p->key = key;
    p->next = hTable[h];
    hTable[h] = p;
}

NodeT *find_elem(NodeT *hTable[M], int key) {
    int h = h_func(key);
    NodeT *p = hTable[h];
    while (p != NULL) {
        if (p->key == key)
            return p;
        p = p->next;
    }
    return NULL;
}

void print_node_key(NodeT *node) {
    if (node != NULL) {
        printf("%d ", node->key);
    } else {
        printf("# ");
    }
}

void test_find(NodeT *hTable[M], int *test_vals, NodeT *expected_vals[]) {
    printf("Testing ");
    for (int i = 0; i < 4; ++i)
        printf("%d ", test_vals[i]);
    printf("against ");
    for (int i = 0; i < 4; ++i)
        print_node_key(expected_vals[i]);
    printf("\n");
    for (int i = 0; i < 4; ++i) {
        NodeT *p = find_elem(hTable, test_vals[i]);
        char *passed = (p == expected_vals[i]) ? "passed" : "failed";
        printf("%d ", test_vals[i]);
        print_node_key(p);
        printf("%s\n", passed);
    }
    printf("\n");
}

void delete_elem(NodeT *hTable[M], int key) {
    NodeT *p = find_elem(hTable, key);
    if (p != NULL) {
        int h = h_func(key);
        NodeT *q = hTable[h];
        if (q == p) {
            hTable[h] = p->next;
        } else {
            while (q->next != p)
                q = q->next;
            q->next = p->next;
        }
        free(p);
    }
}

void print_all(NodeT *hTable[M]) {
    for (int i = 0; i < M; ++i) {
        NodeT *p = hTable[i];
        printf("%d: ", i);
        while (p != NULL) {
            printf("%d ", p->key);
            p = p->next;
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    NodeT *hTable[M];
    for (int i = 0; i < M; ++i)
        hTable[i] = NULL;

    int insert_vals[] = {36, 14, 26, 21, 5, 19, 4, -2, -6};
    for (int i = 0; i < 9; ++i)
        insert_elem(hTable, insert_vals[i]);

    printf("Pre deletion:\n");
    print_all(hTable);

    int test_vals[] = {36, 5, -2, 100};
    NodeT *expected_vals[] = {hTable[1]->next, hTable[5]->next->next, hTable[5], NULL};
    test_find(hTable, test_vals, expected_vals);

    int del_vals[] = {19, 5, 21, 14, 100};
    for (int i = 0; i < 5; ++i)
        delete_elem(hTable, del_vals[i]);

    printf("Post deletion:\n");
    print_all(hTable);

    return 0;
}
