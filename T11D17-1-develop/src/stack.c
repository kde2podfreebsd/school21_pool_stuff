#include "stack.h"

#include <stdlib.h>

Stack *init(int number) {
    Stack *tmp = (Stack *)malloc(sizeof(Stack));
    tmp->value = number;
    tmp->next = NULL;
    return tmp;
}

void push(int number, Stack *root) {
    Stack *head = root;
    while (head->next != NULL) head = head->next;

    Stack *tmp = (Stack *)malloc(sizeof(Stack));
    head->next = tmp;
    tmp->value = number;
    tmp->next = NULL;
}

int pop(Stack *root) {
    if (!root) return 0;

    int result = root->value;
    Stack *head = root, *before_head;

    while (head->next != NULL) {
        if (head != root) before_head = head;
        head = head->next;
    }
    if (head != root) {
        result = head->value;
        before_head->next = NULL;
        free(head);
    } else
        free(root);

    return result;
}

void destroy(Stack *root) {
    Stack *previous = NULL;
    while (root) {
        previous = root;
        root = root->next;
        free(previous);
    }
}