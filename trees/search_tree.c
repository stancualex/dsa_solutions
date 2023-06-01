#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} *NodeT;

NodeT create(int key) {
    NodeT p = malloc(sizeof(struct node));
    p->key = key;
    p->left = p->right = NULL;
    return p;
}

void insert(NodeT *root, int key) {
    if (*root == NULL) {
        *root = create(key);
        return;
    }
    NodeT p = *root;
    while (p != NULL) {
        if (p->key == key)
            return;
        if (p->key < key) {
            if (p->right == NULL) {
                p->right = create(key);
                return;
            }
            p = p->right;
        } else {
            if (p->left == NULL) {
                p->left = create(key);
                return;
            }
            p = p->left;
        }
    }
}

void preorder(NodeT root) {
    if (root == NULL)
        return;

    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void inorder(NodeT root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void postorder(NodeT root) {
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

NodeT search(NodeT root, int key) {
    while (root != NULL) {
        if (root->key == key)
            return root;
        if (root->key < key) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return NULL;
}

NodeT find_min(NodeT root) {
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

NodeT find_max(NodeT root) {
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

NodeT successor(NodeT root, int key) {
    NodeT p = search(root, key);
    if (p == NULL)
        return NULL;
    if (p->right != NULL)
        return find_min(p->right);
    NodeT q = root;
    NodeT succ = NULL;
    while (q != NULL) {
        if (key < q->key) {
            succ = q;
            q = q->left;
        } else if (key > q->key) {
            q = q->right;
        } else {
            break;
        }
    }
    return succ;
}

NodeT predecessor(NodeT root, int key) {
    NodeT p = search(root, key);
    if (p == NULL)
        return NULL;
    if (p->right != NULL)
        return find_max(p->right);
    NodeT q = root;
    NodeT pred = NULL;
    while (q != NULL) {
        if (key < q->key) {
            q = q->left;
        } else if (key > q->key) {
            pred = q;
            q = q->right;
        } else {
            break;
        }
    }
    return pred;
}

int main() {
    NodeT root = NULL;
    int vals[] = {100, 200, 216, 150, 155, 160, 157};
    for (int i = 0; i < 7; ++i)
        insert(&root, vals[i]);

    inorder(root);
    printf("\n");

    printf("%d\n", find_min(root)->key);
    printf("%d\n", find_max(root)->key);
    printf("%d\n", successor(root, 160)->key);
    printf("%d\n", predecessor(root, 157)->key);

    return 0;
}
