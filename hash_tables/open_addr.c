#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 7
#define C1 1
#define C2 1

typedef struct cell {
    int key;
    int status;
} Cell;

int h_prime(int key) {
    key %= M;
    if (key < 0)
        key += M;
    return key;
}

int h_double_prime(int key) {
    key %= M - 2;
    if (key < 0)
        key += M - 2;
    return (M - 2) - key;
}

int linear_probing(int key, int idx) {
    return h_prime(key + idx);
}

int quadratic_probing(int key, int idx) {
    return (h_prime(key) + C1 * idx + C2 * idx * idx) % M;
}

int double_hashing(int key, int idx) {
    return (h_prime(key) + idx * h_double_prime(key)) % M;
}

void insert_key(Cell *hash_table, int key, int (*hash)(int, int)) {
    int idx = 0;
    int h = hash(key, idx);

    while (hash_table[h].status == 1) {
        idx++;
        if (idx >= M)
            return;
        h = hash(key, idx);
    }
    hash_table[h].key = key;
    hash_table[h].status = 1;
}

int find_key(Cell *hash_table, int key, int (*hash)(int, int)) {
    int idx = 0;
    int h = hash(key, idx);

    for (idx = 0; idx < M; ++idx) {
        if (hash_table[h].key == key && hash_table[h].status == 1)
            return h;
        h = hash(key, idx);
    }
    return -1;
}

void delete_key(Cell *hash_table, int key, int (*hash)(int, int)) {
    int h = find_key(hash_table, key, hash);
    if (h != -1)
        hash_table[h].status = 0;
}

void print_table(Cell *hash_table) {
    for (int i = 0; i < M; ++i) {
        printf("%d: ", i);
        if (hash_table[i].status == 1)
            printf("%d", hash_table[i].key);
        printf("\n");
    }
    printf("\n");
}

int main() {
    Cell hash_table[M];
    memset(hash_table, 0, sizeof(hash_table));

    int vals[] = {19, 36, 5, 21, 4, 26, 14, 100};
    int len = sizeof(vals) / sizeof(vals[0]);

    printf("Linear probing:\n");
    for (int i = 0; i < len; ++i)
        insert_key(hash_table, vals[i], linear_probing);
    delete_key(hash_table, 4, linear_probing);
    print_table(hash_table);
    memset(hash_table, 0, sizeof(hash_table));

    printf("Quadratic probing:\n");
    for (int i = 0; i < len; ++i)
        insert_key(hash_table, vals[i], quadratic_probing);
    delete_key(hash_table, 4, quadratic_probing);
    print_table(hash_table);
    memset(hash_table, 0, sizeof(hash_table));

    printf("Double hashing:\n");
    for (int i = 0; i < len; ++i)
        insert_key(hash_table, vals[i], double_hashing);
    delete_key(hash_table, 4, double_hashing);
    print_table(hash_table);

    return 0;
}
