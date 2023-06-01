#include <stdio.h>
#include <stdlib.h>

#define M 7
#define C1 1
#define C2 1

typedef struct cell {
    int key;
    int status;
} CellT;

enum { FREE, OCCUPIED };

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

void insert_key(CellT *cTable, int key, int (*hash)(int, int)) {
    int idx = 0;
    int h = hash(key, idx);

    while (cTable[h].status == OCCUPIED) {
        idx++;
        if (idx >= M)
            return;
        h = hash(key, idx);
    }
    cTable[h].key = key;
    cTable[h].status = OCCUPIED;
}

int find_key(CellT *cTable, int key, int (*hash)(int, int)) {
    int idx = 0;
    int h = hash(key, idx);

    for (idx = 0; idx < M; ++idx) {
        if (cTable[h].key == key && cTable[h].status == OCCUPIED)
            return h;
        h = hash(key, idx);
    }
    return -1;
}

void test_find(CellT *cTable, int *test_vals, int *expected_vals, int (*hash)(int, int)) {
    printf("testing ");
    for (int i = 0; i < 3; ++i)
        printf("%d ", test_vals[i]);
    printf("against ");
    for (int i = 0; i < 3; ++i)
        printf("%d ", expected_vals[i]);
    printf("\n");
    for (int i = 0; i < 3; ++i) {
        int h = find_key(cTable, test_vals[i], hash);
        char *passed = (h == expected_vals[i]) ? "passed" : "failed";
        printf("%d %d %s\n", test_vals[i], h, passed);
    }
    printf("\n");
}

void delete_key(CellT *cTable, int key, int (*hash)(int, int)) {
    int h = find_key(cTable, key, hash);
    if (h != -1)
        cTable[h].status = FREE;
}

void set_table_free(CellT *cTable) {
    for (int i = 0; i < M; ++i)
        cTable[i].status = FREE;
}

void print_table(CellT *cTable) {
    for (int i = 0; i < M; ++i) {
        printf("%d: ", i);
        if (cTable[i].status == OCCUPIED)
            printf("%d", cTable[i].key);
        printf("\n");
    }
    printf("\n");
}

int main() {
    CellT *cTable = malloc(M * sizeof(CellT));
    set_table_free(cTable);

    int vals[M] = {19, 36, 5, 21, 4, 26, 14};
    int testVals[] = {100, 5, 21};

    printf("Linear probing:\n");
    for (int i = 0; i < M; ++i)
        insert_key(cTable, vals[i], linear_probing);
    insert_key(cTable, 100, linear_probing);
    test_find(cTable, testVals, (int[]){-1, 6, 0}, linear_probing);
    delete_key(cTable, 4, linear_probing);
    print_table(cTable);
    set_table_free(cTable);

    printf("Quadratic probing:\n");
    for (int i = 0; i < M; ++i)
        insert_key(cTable, vals[i], quadratic_probing);
    insert_key(cTable, 100, quadratic_probing);
    test_find(cTable, testVals, (int[]){-1, 0, 2}, quadratic_probing);
    delete_key(cTable, 4, quadratic_probing);
    print_table(cTable);
    set_table_free(cTable);

    printf("Double hashing:\n");
    for (int i = 0; i < M; ++i)
        insert_key(cTable, vals[i], double_hashing);
    insert_key(cTable, 100, double_hashing);
    test_find(cTable, testVals, (int[]){-1, 3, 0}, double_hashing);
    delete_key(cTable, 4, double_hashing);
    print_table(cTable);
    set_table_free(cTable);

    free(cTable);
    return 0;
}
