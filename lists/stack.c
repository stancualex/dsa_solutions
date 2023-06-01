#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} NodeT;

typedef struct stack {
    int len;
    NodeT *head;
} Stack;

Stack init() {
    Stack s;
    s.len = 0;
    s.head = NULL;
    return s;
}

NodeT *create(int key) {
    NodeT *p = malloc(sizeof(NodeT));
    p->key = key;
    p->next = NULL;
    return p;
}

void push(Stack *s, int key) {
    s->len++;
    NodeT *p = create(key);
    if (s->head == NULL) {
        s->head = p;
        return;
    }

    p->next = s->head;
    s->head = p;
}

int pop(Stack *s) {
    if (s->head == NULL)
        return -1;

    s->len--;
    NodeT *p = s->head;
    int key = p->key;
    s->head = p->next;
    free(p);

    return key;
}

int peek(Stack s) {
    return s.head->key;
}

void print_stack(Stack s) {
    for (NodeT *p = s.head; p != NULL; p = p->next)
        printf("%d ", p->key);
    printf("\n");
}

void drop(Stack *s) {
    while (s->head != NULL) {
        NodeT *p = s->head;
        s->head = s->head->next;
        free(p);
    }
}

int main() {
    Stack s = init();
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 8; ++i)
        push(&s, arr[i]);
    print_stack(s);
    printf("%d\n", peek(s));
    printf("len: %d\n", s.len);

    for (int i = 0; i < 9; ++i)
        printf("%d ", pop(&s));
    printf("\n");
    printf("len: %d\n", s.len);

    drop(&s);
    return 0;
}
