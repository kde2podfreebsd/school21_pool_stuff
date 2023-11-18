#ifndef STACK_H
#define STACK_H

typedef struct stack {
    int value;
    struct stack *next;
} Stack;

struct stack *init(int number);
void push(int number, Stack *root);
int pop(Stack *root);
void destroy(Stack *root);

#endif