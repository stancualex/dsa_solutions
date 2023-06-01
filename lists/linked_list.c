#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} NodeT;

NodeT *create(int key) {
    NodeT *p = malloc(sizeof(NodeT));
    p->key = key;
    p->next = NULL;
    return p;
}

void insert_first(NodeT **first, int key) {
    if (*first == NULL) {
        *first = create(key);
    } else {
        NodeT *p = create(key);
        p->next = *first;
        *first = p;
    }
}

void insert_last(NodeT **first, NodeT **last, int key) {
    if (*first == NULL && *last == NULL) {
        *first = *last = create(key);
    } else {
        NodeT *p = create(key);
        (*last)->next = p;
        *last = p;
    }
}

NodeT *search_key(NodeT *first, int key) {
    for (NodeT *p = first; p != NULL; p = p->next)
        if (p->key == key)
            return p;
    return NULL;
}

void print_node_key(NodeT *node) {
    if (node != NULL) {
        printf("%d ", node->key);
    } else {
        printf("# ");
    }
}

void test_search(NodeT *first, int *test_vals, NodeT *expected_vals[]) {
    printf("testing ");
    for (int i = 0; i < 4; ++i)
        printf("%d ", test_vals[i]);
    printf("against ");
    for (int i = 0; i < 4; ++i)
        print_node_key(expected_vals[i]);
    printf("\n");
    for (int i = 0; i < 4; ++i) {
        NodeT *p = search_key(first, test_vals[i]);
        char *passed = (p == expected_vals[i]) ? "passed" : "failed";
        printf("%d ", test_vals[i]);
        print_node_key(p);
        printf("%s\n", passed);
    }
    printf("\n");
}

void insert_after(NodeT **first, NodeT **last, int key, int after_key) {
    NodeT *p = search_key(*first, after_key);
    if (p != NULL) {
        if (p == *last) {
            insert_last(first, last, key);
        } else {
            NodeT *q = create(key);
            q->next = p->next;
            p->next = q;
        }
    }
}

void delete_first(NodeT **first, NodeT **last) {
    if (*first != NULL) {
        NodeT *p = *first;
        *first = (*first)->next;
        free(p);
        if (*first == NULL)
            *last = NULL;
    }
}

void delete_last(NodeT **first, NodeT **last) {
    if (*first != NULL) {
        if (*first == *last) {
            free(*first);
            *first = *last = NULL;
        } else {
            NodeT *p = *first;
            while (p->next != *last)
                p = p->next;
            free(*last);
            *last = p;
            p->next = NULL;
        }
    }
}

void delete_key(NodeT **first, NodeT **last, int key) {
    if (*first != NULL) {
        if ((*first)->key == key) {
            delete_first(first, last);
        } else {
            NodeT *p = *first;
            while (p->next != NULL && p->next->key != key)
                p = p->next;
            if (p->next != NULL) {
                NodeT *q = p->next;
                p->next = q->next;
                free(q);
                if (p->next == NULL)
                    *last = p;
            }
        }
    }
}

void print_list(NodeT *first) {
    NodeT *p = first;
    while (p != NULL) {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("\n");
}

void free_list(NodeT **first, NodeT **last) {
    NodeT *p = *first;
    while (p != NULL) {
        NodeT *q = p;
        p = p->next;
        free(q);
    }
    *first = *last = NULL;
}

int main() {
    NodeT *first = NULL;
    NodeT *last = NULL;

    insert_last(&first, &last, 1);
    insert_last(&first, &last, 2);
    insert_last(&first, &last, 3);

    insert_first(&first, 4);
    insert_first(&first, 5);
    insert_first(&first, 6);

    print_list(first);

    int test_vals[] = {3, 6, 4, 7};
    NodeT *expected_vals[] = {last, first, first->next->next, NULL};
    test_search(first, test_vals, expected_vals);

    insert_after(&first, &last, 7, 2);
    insert_after(&first, &last, 8, 3);
    insert_after(&first, &last, 9, 5);

    delete_first(&first, &last);
    delete_last(&first, &last);
    delete_key(&first, &last, 2);

    print_list(first);

    free_list(&first, &last);
    return 0;
}
