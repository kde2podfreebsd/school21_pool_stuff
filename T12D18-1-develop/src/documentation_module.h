#ifndef DOCUMENTATION_MODULE_H
#define DOCUMENTATION_MODULE_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define Documents "Linked lists", "Queues", "Maps", "Binary Trees"
#define Available_document "Binary Trees"
#define Documents_count 4

typedef struct availability_node {
    char document[16];
    int status;
    struct availability_node *next;
} Node;

Node *check_available_documentation_module(int (*validate)(char *), int document_count, ...);
int validate(char *data);
void output_availability(Node *list_root);

Node *init(int number);
void push(char str[16], int number, Node *root);
void destroy(Node *root);

#endif