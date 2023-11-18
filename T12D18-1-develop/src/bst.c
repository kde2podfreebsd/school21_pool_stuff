#include "bst.h"

#include <stdlib.h>

t_btree *bstree_create_node(int item) {
    t_btree *tmp = (t_btree *)malloc(sizeof(t_btree));
    tmp->item = item;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
    t_btree *tmp = bstree_create_node(item);

    if (root != NULL) {
        if (cmpf(item, root->item))
            root->left = tmp;
        else
            root->right = tmp;
    }
}

void bstree_destroy(t_btree *root) {
    if (!root) return;

    bstree_destroy(root->left);
    bstree_destroy(root->right);

    free(root);
}

void bstree_apply_infix(t_btree *root, void (*applyf)(int)) {
    if (!root) return;

    bstree_apply_infix(root->left, applyf);
    applyf(root->item);
    bstree_apply_infix(root->right, applyf);
}

void bstree_apply_prefix(t_btree *root, void (*applyf)(int)) {
    if (!root) return;

    applyf(root->item);
    bstree_apply_prefix(root->left, applyf);
    bstree_apply_prefix(root->right, applyf);
}

void bstree_apply_postfix(t_btree *root, void (*applyf)(int)) {
    if (!root) return;

    bstree_apply_postfix(root->left, applyf);
    bstree_apply_postfix(root->right, applyf);
    applyf(root->item);
}