#include <stdio.h>

#include "bst.h"

void bst_traverse_test();
int is_A_less_than_B(int A, int B);
void print_tree_item(int item);

int main() {
    bst_traverse_test();

    return 0;
}

void bst_traverse_test() {
    t_btree *root;
    root = bstree_create_node(10);
    bstree_insert(root, 5, is_A_less_than_B);
    bstree_insert(root, 13, is_A_less_than_B);
    bstree_insert(root->left, 3, is_A_less_than_B);
    bstree_insert(root->left, 7, is_A_less_than_B);
    bstree_insert(root->right, 11, is_A_less_than_B);
    bstree_insert(root->right, 15, is_A_less_than_B);

    printf("Test case %d (infix traverse)\n", 1);
    bstree_apply_infix(root, print_tree_item);
    printf("\n\n");

    printf("Test case %d (prefix traverse)\n", 2);
    bstree_apply_prefix(root, print_tree_item);
    printf("\n\n");

    printf("Test case %d (postfix traverse)\n", 3);
    bstree_apply_postfix(root, print_tree_item);

    bstree_destroy(root);
}

int is_A_less_than_B(int A, int B) { return A < B; }

void print_tree_item(int item) { printf("%d ", item); }