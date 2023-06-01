#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int key;
    struct node *next;
} *NodeT;

typedef struct queue {
    int len;
    NodeT head;
    NodeT tail;
} Queue;

typedef struct stack {
    int len;
    NodeT head;
} Stack;

typedef struct graph {
    int n;
    int **m;
} Graph;

NodeT create(int key) {
    NodeT p = malloc(sizeof(struct node));
    p->key = key;
    p->next = NULL;
    return p;
}

Queue init_q() {
    Queue q;
    q.head = q.tail = NULL;
    q.len = 0;
    return q;
}

void enqueue(Queue *q, int key) {
    NodeT p = create(key);
    if (q->len == 0) {
        q->len++;
        q->head = q->tail = p;
        return;
    }

    q->len++;
    q->tail->next = p;
    q->tail = p;
}

int deque(Queue *q) {
    if (q->len == 0) {
        q->head = q->tail = NULL;
        return -1;
    }

    q->len--;
    NodeT p = q->head;
    int key = p->key;
    q->head = p->next;
    free(p);
    return key;
}

void print_q(Queue q) {
    for (NodeT p = q.head; p != NULL; p = p->next)
        printf("%d ", p->key);
    printf("\n");
}

Stack init_s() {
    Stack s;
    s.len = 0;
    s.head = NULL;
    return s;
}

void push(Stack *s, int key) {
    NodeT p = create(key);
    if (s->len == 0) {
        s->len++;
        s->head = p;
        return;
    }

    s->len++;
    p->next = s->head;
    s->head = p;
}

int pop(Stack *s) {
    if (s->len == 0) {
        s->head = NULL;
        return -1;
    }

    s->len--;
    NodeT p = s->head;
    int key = p->key;
    s->head = p->next;
    free(p);
    return key;
}

void print_s(Stack s) {
    for (NodeT p = s.head; p != NULL; p = p->next)
        printf("%d ", p->key);
    printf("\n");
}

void bfs(Graph g, int start) {
    int visited[g.n];
    memset(visited, 0, sizeof(visited));
    Queue q = init_q();
    enqueue(&q, start - 1);

    while (q.len > 0) {
        int u = deque(&q);
        if (visited[u] == 1)
            continue;
        printf("%d ", u + 1);
        visited[u] = 1;
        for (int v = 0; v < g.n; ++v)
            if (g.m[u][v] == 1 && visited[v] == 0)
                enqueue(&q, v);
    }
    printf("\n");
}

void dfs(Graph g, int start) {
    int visited[g.n];
    memset(visited, 0, sizeof(visited));
    Stack s = init_s();
    push(&s, start - 1);

    while (s.len > 0) {
        int u = pop(&s);
        if (visited[u] == 1)
            continue;
        printf("%d ", u + 1);
        visited[u] = 1;
        for (int v = 0; v < g.n; ++v)
            if (g.m[u][v] == 1 && visited[v] == 0)
                push(&s, v);
    }
    printf("\n");
}

int main() {
    Graph g;
    FILE *f = fopen("graph.txt", "r");
    if (f == NULL) {
        perror("Error opening file");
        return errno;
    }

    fscanf(f, "%d", &g.n);
    g.m = malloc(g.n * sizeof(int *));
    for (int i = 0; i < g.n; ++i)
        g.m[i] = calloc(g.n, sizeof(int));

    int u, v;
    while (fscanf(f, "%d %d", &u, &v) == 2) {
        g.m[u - 1][v - 1] = 1;
        // g.m[v - 1][u - 1] = 1;
    }

    for (int i = 0; i < g.n; ++i) {
        for (int j = 0; j < g.n; ++j)
            printf("%d ", g.m[i][j]);
        printf("\n");
    }
    printf("\n");

    bfs(g, 1);
    dfs(g, 1);

    for (int i = 0; i < g.n; ++i)
        free(g.m[i]);
    free(g.m);
    fclose(f);
    return 0;
}
