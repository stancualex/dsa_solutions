#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} *NodeT;

NodeT create(int key) {
    NodeT p = malloc(sizeof(NodeT));
    p->key = key;
    p->left = NULL;
    p->right = NULL;
    return p;
}

NodeT read(FILE *f) {
    char s[100];
    fscanf(f, "%s", s);
    if (s[0] == '#') {
        return NULL;
    }
    NodeT p = create(atoi(s));
    p->left = read(f);
    p->right = read(f);
    return p;
}

void preorder(NodeT root) {
    if (root == NULL) {
        printf("# ");
        return;
    }
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void inorder(NodeT root) {
    if (root == NULL) {
        printf("# ");
        return;
    }
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void postorder(NodeT root) {
    if (root == NULL) {
        printf("# ");
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

int leaf_node(NodeT root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->key);
        return 1;
    }
    return leaf_node(root->left) + leaf_node(root->right);
}

int internal_node(NodeT root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    return 1 + internal_node(root->left) + internal_node(root->right);
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int height(NodeT root) {
    if (root == NULL)
        return -1;
    return 1 + max(height(root->left), height(root->right));
}

NodeT search(NodeT root, int key) {
    if (root == NULL)
        return NULL;
    if (root->key == key)
        return root;
    NodeT p = search(root->left, key);
    if (p != NULL)
        return p;
    return search(root->right, key);
}

void free_tree(NodeT root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    FILE *f = fopen("tree.txt", "r");
    if (f == NULL) {
        perror("Error opening file");
        return errno;
    }

    NodeT root = read(f);

    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");

    leaf_node(root);
    printf("\n");

    printf("%d\n", internal_node(root));
    printf("%d\n\n", height(root));

    free_tree(root);
    return 0;
}
