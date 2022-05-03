#include <stdio.h>
#include <stdlib.h>
struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};
struct Node *Insert(struct Node *tree, int x, struct Node *parent);
struct Node* Search(struct Node *tree, int k);
struct Node *Min(struct Node *tree);
void Transplant(struct Node *tree, struct Node *current, struct Node *changeto);
void Erase(struct Node *tree, struct Node *del_elem);
void InOrder(struct Node *tree);
void tree_destroy(struct Node * tree);

int main() {
    struct Node *tree = NULL;
    int x = 0;
    scanf("%d", &x);
    int is_root = x;
    while (x != 0) {
        tree = Insert(tree, x, NULL);
        scanf("%d", &x);
    }
    printf("\n BEFORE:");
    InOrder(tree);
    printf("======\n");
    printf("Element you want to delete : ");
    int delete_elem;
    scanf("%d", &delete_elem);
    if (is_root == delete_elem) {
        InOrder(tree->left);
        InOrder(tree->right);
    }
    else { 
        struct Node *del_Elem_struct = Search(tree, delete_elem);
        Erase(tree, del_Elem_struct);
        printf("\n");
        InOrder(tree);
    }
    return 0;
}


struct Node *Insert(struct Node *tree, int x, struct Node *parent) {
    if (tree == NULL) {
        struct Node *tree = (struct Node *)malloc(sizeof(struct Node));
        tree->val = x;
        tree->left = NULL;
        tree->right = NULL;
        tree->parent = parent; 
        return tree;
    }

    if (x < tree->val) {
        tree->left = Insert(tree->left, x, tree);
        return tree;
    }

    if (x > tree->val) {
        tree->right = Insert(tree->right, x, tree);
        return tree;
    }
    return tree;
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

struct Node *Min(struct Node *tree) {
    if (tree->left == NULL) {
        return tree;
    }
    Min(tree->left);
}

void Transplant(struct Node *tree, struct Node *current, struct Node *changeto) {
    if (current->parent->left == current) {
        current->parent->left = changeto;
    } 
    else {
        current->parent->right = changeto;    
    }
    if ( changeto != NULL) {
        changeto->parent = current->parent;
    }
}


void Erase(struct Node *tree, struct Node *del_elem) {
    if (del_elem->left == NULL)  {
        Transplant(tree, del_elem, del_elem->right);
    }
    else if (del_elem->right == NULL)  {
        Transplant(tree, del_elem, del_elem->left);
    }
    else { 
        struct Node *Minimum = Min(del_elem->right);
        if (Minimum->parent != del_elem) {
            Transplant(tree, Minimum, Minimum->right);
            Minimum->right = del_elem->right;
            Minimum->parent->right = Minimum;
        }
        Transplant(tree, del_elem, Minimum);
        Minimum->left = del_elem->left;
        Minimum->parent->left = Minimum;
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