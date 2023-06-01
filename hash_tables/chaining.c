#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 7

typedef struct node {
    int key;
    struct node *next;
} *NodeT;

int hash_func(int key) {
    key %= M;
    if (key < 0)
        key += M;
    return key;
}

void insert_key(NodeT hash_table[M], int key) {
    int h = hash_func(key);
    NodeT p = malloc(sizeof(struct node));
    p->key = key;
    p->next = hash_table[h];
    hash_table[h] = p;
}

NodeT find_key(NodeT hash_table[M], int key) {
    int h = hash_func(key);
    for (NodeT p = hash_table[h]; p != NULL; p = p->next)
        if (p->key == key)
            return p;
    return NULL;
}

void delete_key(NodeT hash_table[M], int key) {
    NodeT p = find_key(hash_table, key);
    if (p == NULL)
        return;

    int h = hash_func(key);
    NodeT q = hash_table[h];
    if (q == p) {
        hash_table[h] = p->next;
    } else {
        while (q->next != p)
            q = q->next;
        q->next = p->next;
    }
    free(p);
}

void print_list(NodeT head) {
    for (NodeT p = head; p != NULL; p = p->next)
        printf("%d ", p->key);
    printf("\n");
}

void print_all(NodeT hash_table[M]) {
    for (int i = 0; i < M; ++i) {
        printf("%d: ", i);
        print_list(hash_table[i]);
    }
    printf("\n");
}

int main() {
    NodeT hash_table[M];
    memset(hash_table, 0, sizeof(hash_table));

    int ins_vals[] = {36, 14, 26, 21, 5, 19, 4, -2, -6};
    int len_ins = sizeof(ins_vals) / sizeof(ins_vals[0]);
    for (int i = 0; i < len_ins; ++i)
        insert_key(hash_table, ins_vals[i]);

    printf("Pre deletion:\n");
    print_all(hash_table);

    int del_vals[] = {19, 5, 21, 14, 100};
    int len_del = sizeof(del_vals) / sizeof(del_vals[0]);
    for (int i = 0; i < len_del; ++i)
        delete_key(hash_table, del_vals[i]);

    printf("Post deletion:\n");
    print_all(hash_table);

    return 0;
}
