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
    NodeT *lists;
} Graph;

NodeT create(int key) {
    NodeT p = malloc(sizeof(struct node));
    p->key = key;
    p->next = NULL;
    return p;
}

void insert_first(NodeT *head, int key) {
    NodeT p = create(key);
    if (*head == NULL) {
        *head = p;
        return;
    }

    p->next = *head;
    *head = p;
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
    s.head = NULL;
    s.len = 0;
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

void print_list(NodeT head) {
    for (NodeT p = head; p != NULL; p = p->next)
        printf("%d ", p->key + 1);
    printf("\n");
}

void print_graph_lists(Graph g) {
    for (int i = 0; i < g.n; ++i) {
        printf("%d: ", i + 1);
        print_list(g.lists[i]);
    }
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
        for (NodeT p = g.lists[u]; p != NULL; p = p->next)
            if (visited[p->key] == 0)
                enqueue(&q, p->key);
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
        for (NodeT p = g.lists[u]; p != NULL; p = p->next)
            if (visited[p->key] == 0)
                push(&s, p->key);
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
    g.lists = calloc(g.n, sizeof(NodeT));

    int u, v;
    while (fscanf(f, "%d %d", &u, &v) == 2) {
        insert_first(&g.lists[u - 1], v - 1);
        // insert_first(&g.lists[v - 1], u - 1);
    }

    print_graph_lists(g);

    bfs(g, 1);
    dfs(g, 1);

    fclose(f);
    free(g.lists);
    return 0;
}
