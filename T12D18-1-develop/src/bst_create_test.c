#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define CASES_N 2

void bst_create_test();

int main() {
    bst_create_test();
    return 0;
}

void bst_create_test() {
    int tests[CASES_N] = {21, 666};

    for (int i = 0; i < CASES_N; i++) {
        printf("Test case %d\n", i + 1);
        printf("Input tree item: %d\n", tests[i]);
        t_btree *root = bstree_create_node(tests[i]);
        if (root && root->item && root->item == tests[i])
            printf("SUCCESS. Node created: item: %d, left: %p, right: %p", root->item, root->left,
                   root->right);
        else if (root && root->item && root->item == tests[i])
            printf("FAIL. Node didn't created");
        if (i != CASES_N - 1) printf("\n\n");
        free(root);
    }
}