#include "stack.h"

#include <stdio.h>

void print_stack(Stack *root);

int main() {
#ifdef STACK_TEST
    Stack *int_stack_root = init(0);
    printf("Pushing to stack 21, then 42...\n");
    push(21, int_stack_root);
    push(42, int_stack_root);
    printf("Current stack values: ");
    print_stack(int_stack_root);
    printf("\n");

    printf("Popping one lement from stack...\n");
    int element = pop(int_stack_root);
    printf("Current stack values: ");
    print_stack(int_stack_root);
    printf("\n");
    printf("Popped value: %d", element);

    if (int_stack_root != NULL) destroy(int_stack_root);
#endif

    return 0;
}

void print_stack(Stack *root) {
    Stack *tmp = root;
    while (tmp != NULL) {
        printf("%d", tmp->value);
        tmp = tmp->next;
        if (tmp != NULL) printf(" ");
    }
    printf("\n");
}