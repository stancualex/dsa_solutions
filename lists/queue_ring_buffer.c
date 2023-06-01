#include <stdio.h>

#define CAPACITY 10

typedef struct queue {
    int vec[CAPACITY];
    int size;
    int head, tail;
} Queue;

void init(Queue *q) {
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}

void enqueue(Queue *q, int key) {
    if (q->size == CAPACITY) {
        printf("Queue is full!\n");
        return;
    }
    q->vec[q->tail] = key;
    q->tail = (q->tail + 1) % CAPACITY;
    q->size++;
}

int deque(Queue *q) {
    if (q->size == 0) {
        printf("Queue is empty!\n");
        return -1;
    }
    int key = q->vec[q->head];
    q->head = (q->head + 1) % CAPACITY;
    q->size--;
    return key;
}

void print_queue(Queue q) {
    for (int i = 0; i < q.size; ++i)
        printf("%d ", q.vec[(q.head + i) % CAPACITY]);
    printf("\n");
}

int main() {
    Queue q;
    init(&q);

    int vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (int i = 0; i < 11; ++i)
        enqueue(&q, vals[i]);
    print_queue(q);

    for (int i = 0; i < 11; ++i)
        printf("%d ", deque(&q));
    printf("\n");

    return 0;
}
