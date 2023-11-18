#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void bst_insert_test();
int is_A_less_than_B(int A, int B);

int main() {
    bst_insert_test();
    return 0;
}

void bst_insert_test() {
    t_btree *root, *tmp;

    printf("Test case %d\n", 1);
    root = bstree_create_node(10);
    printf("Tree root created: item: %d, left: %p, right: %p\n", root->item, root->left, root->right);
    int test1[2] = {9, 8};

    bstree_insert(root, test1[0], is_A_less_than_B);
    tmp = root->left;
    printf("Inserted item: %d, root target: %s\n", test1[0], tmp->item == test1[0] ? "left" : "right");
    printf("Tree root after insertion: item: %d, left: %p, right: %p\n", root->item, root->left, root->right);
    free(tmp);

    bstree_insert(root, test1[1], is_A_less_than_B);
    tmp = root->left;
    printf("Inserted item: %d, root target: %s\n", test1[1], tmp->item == test1[1] ? "left" : "right");
    printf("Tree root after insertion: item: %d, left: %p, right: %p\n", root->item, root->left, root->right);
    free(tmp);

    bstree_destroy(root);
    free(root);

    printf("\n\n");

    printf("Test case %d\n", 2);
    root = bstree_create_node(10);
    printf("Tree root created: item: %d, left: %p, right: %p\n", root->item, root->left, root->right);
    int test2[2] = {11, 8};

    bstree_insert(root, test2[0], is_A_less_than_B);
    tmp = root->right;
    printf("Inserted item: %d, root target: %s\n", test2[0], tmp->item == test2[0] ? "right" : "left");
    printf("Tree root after insertion: item: %d, left: %p, right: %p\n", root->item, root->left, root->right);
    free(tmp);

    bstree_insert(root, test2[1], is_A_less_than_B);
    tmp = root->left;
    printf("Inserted item: %d, root target: %s\n", test2[1], tmp->item == test2[1] ? "left" : "right");
    printf("Tree root after insertion: item: %d, left: %p, right: %p\n", root->item, root->left, root->right);
    free(tmp);

    bstree_destroy(root);
    free(root);
}

int is_A_less_than_B(int A, int B) { return A < B; }