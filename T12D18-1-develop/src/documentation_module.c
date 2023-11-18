#include "documentation_module.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

Node *check_available_documentation_module(int (*validate)(char *), int document_count, ...) {
    Node *availability_list_root = init(-1);
    va_list arg_pointer;
    va_start(arg_pointer, document_count);

    for (int i = 0; i < document_count; i++) {
        char *str = va_arg(arg_pointer, char *);
        int status = validate(str);
        push(str, status, availability_list_root);
    }

    va_end(arg_pointer);
    return availability_list_root;
}

int validate(char *data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

void output_availability(Node *list_root) {
    Node *tmp = list_root->next;
    while (tmp) {
        printf("%s : %savailable", tmp->document, tmp->status ? "" : "un");
        if (tmp->next) printf("\n");
        tmp = tmp->next;
    }
}

Node *init(int number) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    strcpy(tmp->document, "root");
    tmp->status = number;
    tmp->next = NULL;
    return tmp;
}

void push(char str[16], int number, Node *root) {
    Node *head = root;
    while (head->next != NULL) head = head->next;

    Node *tmp = (Node *)malloc(sizeof(Node));
    strcpy(tmp->document, str);
    head->next = tmp;
    tmp->status = number;
    tmp->next = NULL;
}

void destroy(Node *root) {
    Node *previous = NULL;
    while (root) {
        previous = root;
        root = root->next;
        free(previous);
    }
}