#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

StackNode* init(StackNode* stack_node, int data) {
    stack_node = (StackNode*)malloc(sizeof(StackNode));
    if(stack_node == NULL) return NULL;

    stack_node->data = data;
    stack_node->next = NULL;

    return stack_node;
}

StackNode* push(StackNode* top_node, int data) {
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if(new_node == NULL) return top_node;

    new_node->data = data;
    new_node->next = top_node;

    return new_node;
}

StackNode* pop(StackNode* poped_node){
    if(poped_node == NULL) return NULL;

    StackNode* top_node = poped_node->next;
    
    free(poped_node);

    return top_node;
}

void destroy(StackNode* stack_node){
    while(stack_node){
        stack_node = pop(stack_node);
    }
}

///////////////

#ifndef S21_STACK
#define S21_STACK

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

StackNode*  init(StackNode* stack_node, int data);
StackNode*  push(StackNode* top_node, int data);
StackNode*  pop(StackNode* poped_node);
void        destroy(StackNode* sn);

#endif
