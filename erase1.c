#include <stdio.h>
#include <stdlib.h>
struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Node * Insert(struct Node * tree, int x);
struct Node *Minimum(struct Node *tree); 
struct Node *Search(struct Node *tree, int k);
struct Node *parent_search(struct Node *tree, struct Node *Search); 
void Transplant(struct Node *tree, struct Node *current, struct Node *changeTo);
void Erase(struct Node *tree, struct Node *Find);
void InOrder(struct Node *tree);
void tree_destroy(struct Node * tree);

int main() {
    struct Node * tree = NULL;
    int x = 0;
    printf("fill a binary tree\nType 0 to stop : \n");
    scanf("%d", &x);
    while (x != 0) {
        tree = Insert(tree, x);
        scanf("%d", &x);
    }
    InOrder(tree);
    printf("\n");
    printf("Type element you want to erase:");
    int k = 0;
    scanf("%d", &k); // элемент который удаляем
    printf("\n");
    struct Node *Find = Search(tree, k);
    Erase(tree, Find);
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

struct Node *Minimum(struct Node *tree) {
    if (tree->left == NULL) {
        return tree;
    }
    return Minimum(tree->left);
}

struct Node* Search(struct Node *tree, int k) {
    if ((tree == NULL) || (k == tree->val)) {
        return tree;
    } 
    if (k < tree->val) {
        return Search(tree->left, k);
    }
    else {
        return Search(tree->right, k);
    }
}
struct Node *parent_search(struct Node *tree, struct Node *Search) {
    if ((tree->right == Search) || ((tree->left) == Search)) {
        return tree;
    }
    else {
        if (tree->val < Search->val) {
            parent_search(tree->right, Search);
        }
        else {
            parent_search(tree->left, Search);
        }
    }
}




void Transplant(struct Node *tree, struct Node *current, struct Node *changeTo) {
    struct Node *current_parent = parent_search(tree, current);
    if ( current = current_parent->left) {
        current_parent->left = changeTo;
    }
    else {
        current_parent->right = changeTo;
    }
    if (changeTo != NULL) {
        struct Node *changeto_parent = parent_search(tree, changeTo);
        changeto_parent = current_parent;
    }
}

void Erase(struct Node *tree, struct Node *z) {  // z - хотим удалить
    if (z->left == NULL) {
        Transplant(tree, z, z->right);
    }
    else if (z->right == NULL) {
        Transplant(tree, z, z->left);
    }
    else {
        struct Node *y = Minimum(z->right);
        struct Node *y_parent = parent_search(tree, y);
        struct Node *y_left = parent_search(tree, y->left);
        struct Node *y_right = parent_search(tree, y->right);
        if (y_parent != z) {
            Transplant(tree,y, y->right);
            y->right = z->right;
            y_right = y; 
        }
        Transplant(tree, z, y);
        y->left = z->left;
        y_left = y;
    }

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