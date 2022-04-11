#include <stdio.h>
#include <stdlib.h>
struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};

struct Node * Insert(struct Node * tree, int x);
void InOrder(struct Node *tree);



void tree_destroy(struct Node * tree);

int main() {
    struct Node * tree = NULL;
    int x = 0;
    scanf("%d", &x);
    while (x != 0) {
        tree = Insert(tree, x);
        scanf("%d", &x);
    }
    InOrder(tree);
    tree_destroy(tree);
    return 0;
}



struct Node * Insert(struct Node * tree, int x) {
    if(tree == NULL) {
        struct Node * tree = (struct Node *)malloc(sizeof(struct Node));
        tree->val = x;
        tree->left = NULL;
        tree->right = NULL;
        return tree;
    }
    if(x < tree->val) {
        tree->left = Insert(tree->left, x);
        return tree; 
    }
    if(x > tree->val) {
        tree->right = Insert(tree->right, x);
        return tree;
    }
    return tree;
}

void InOrder(struct Node *tree) {
    if (tree != NULL) {
        InOrder(tree->left);
        printf("%d ", (int)tree->val);
        InOrder(tree->right);
    }
}






void tree_destroy(struct Node * tree) {
    if(tree != NULL) {
        tree_destroy(tree->left);

        tree_destroy(tree->right);
        free(tree);
    }
}