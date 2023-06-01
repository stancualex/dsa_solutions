#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} NodeT;

typedef struct queue {
    int size;
    NodeT *head;
    NodeT *tail;
} Queue;

void init(Queue *q) {
    q->head = q->tail = NULL;
    q->size = 0;
}

NodeT *create(int key) {
    NodeT *p = malloc(sizeof(NodeT));
    p->key = key;
    p->next = NULL;
    return p;
}

void enqueue(Queue *q, int key) {
    NodeT *p = create(key);
    if (q->size == 0) {
        q->head = q->tail = p;
        q->size++;
        return;
    }
    q->size++;
    q->tail->next = p;
    q->tail = p;
}

int deque(Queue *q) {
    if (q->size == 0) {
        q->tail = NULL;
        return -1;
    }

    q->size--;
    NodeT *p = q->head;
    int key = p->key;
    q->head = p->next;
    free(p);

    return key;
}

int peek(Queue q) {
    return q.head->key;
}

void print_queue(Queue q) {
    for (NodeT *p = q.head; p != NULL; p = p->next)
        printf("%d ", p->key);
    printf("\n");
}

int main() {
    Queue q;
    init(&q);
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 8; ++i)
        enqueue(&q, arr[i]);

    print_queue(q);
    printf("%d\n", peek(q));
    for (int i = 0; i < 9; ++i)
        printf("%d ", deque(&q));
    printf("\n");

    return 0;
}
