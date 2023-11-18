#include "data_structs.h"

#include <stdio.h>
#include <stdlib.h>

Expression_node *create_expression_node(char lexeme) {
    Expression_node *tmp = (Expression_node *)malloc(sizeof(Expression_node));
    tmp->lexeme_char = lexeme;
    tmp->next = NULL;
    return tmp;
}

void push_to_expression(Expression_node *node, Expression_node *root) {
    Expression_node *head = root;
    while (head->next != NULL) head = head->next;

    head->next = node;
    node->next = NULL;
}

void destroy_expression(Expression_node *root) {
    Expression_node *previous = NULL;
    while (root) {
        previous = root;
        root = root->next;
        free(previous);
    }
}

void parse_input_to_expression(Expression_node *root, int *error) {
    char ch = getchar();
    while (ch != '\n' && !*error) {
        if ((ch - '0' >= 0 && ch - '0' <= 9) || ch == '.' || ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '(' || ch == ')' || ch == 'x') {
            push_to_expression(create_expression_node(ch), root);

        } else if (ch == 's') {
            ch = getchar();
            if (ch == 'i' && getchar() == 'n')
                push_to_expression(create_expression_node('s'), root);
            else if (ch == 'q' && getchar() == 'r' && getchar() == 't')
                push_to_expression(create_expression_node('q'), root);
            else
                *error = 1;

        } else if (ch == 'c') {
            ch = getchar();
            if (ch == 'o' && getchar() == 's')
                push_to_expression(create_expression_node('c'), root);
            else if (ch == 't' && getchar() == 'g')
                push_to_expression(create_expression_node('g'), root);
            else
                *error = 1;

        } else if (ch == 't') {
            if (getchar() == 'a' && getchar() == 'n')
                push_to_expression(create_expression_node('t'), root);
            else
                *error = 1;

        } else if (ch == 'l') {
            if (getchar() == 'n')
                push_to_expression(create_expression_node('l'), root);
            else
                *error = 1;

        } else if (ch == ' ') {
        } else {
            *error = 1;
        }
        ch = getchar();
    }
}

void convert_expression_digits_to_numbers(Expression_node *root) {
    Expression_node *tmp = root;

    while (tmp) {
        if ((tmp->lexeme_char - '0' >= 0 && tmp->lexeme_char - '0' <= 9) || tmp->lexeme_char == '.') {
            int inc = tmp->lexeme_char == '.' ? -1 : 1;
            double dec = 0.1;
            double number_int = tmp->lexeme_char == '.' ? 0 : tmp->lexeme_char - '0';
            double number_float = 0.0;
            Expression_node *tmp_digit = tmp->next;
            while (tmp_digit && ((tmp_digit->lexeme_char - '0' >= 0 && tmp_digit->lexeme_char - '0' <= 9) ||
                                 tmp_digit->lexeme_char == '.')) {
                if (tmp_digit->lexeme_char == '.') {
                    inc = -1;
                } else {
                    if (inc == 1) {
                        number_int = number_int * 10 + (tmp_digit->lexeme_char - '0');
                    } else {
                        number_float += (tmp_digit->lexeme_char - '0') * dec;
                        dec /= 10;
                    }
                }
                tmp->next = tmp_digit->next;
                free(tmp_digit);
                tmp_digit = tmp->next;
            }
            double number = number_int + number_float;
            tmp->lexeme_number = number;
            tmp = tmp_digit;
        } else
            tmp = tmp->next;
    }
}

Stack *create_stack_node(char operation, double number) {
    Stack *tmp = (Stack *)malloc(sizeof(Stack));
    tmp->operation = operation;
    tmp->number = number;
    tmp->next = NULL;
    return tmp;
}

Stack *get_head(Stack *root) {
    Stack *head = root;
    while (head->next != NULL) head = head->next;
    return head;
}

Stack *push_to_stack(char operation, double number, Stack *root) {
    Stack *head = get_head(root);
    Stack *tmp = (Stack *)malloc(sizeof(Stack));
    head->next = tmp;
    tmp->operation = operation;
    tmp->number = number;
    tmp->next = NULL;
    return tmp;
}

char pop_from_stack_char(Stack *root) {
    if (!root) return 'r';

    char result = root->operation;
    Stack *head = root, *before_head;

    while (head->next != NULL) {
        before_head = head;
        head = head->next;
    }
    if (head != root) {
        result = head->operation;
        before_head->next = NULL;
        free(head);
    } else
        free(root);

    return result;
}

double pop_from_stack_double(Stack *root) {
    if (!root) return 0;

    double result = root->number;
    Stack *head = root, *before_head;

    while (head->next != NULL) {
        before_head = head;
        head = head->next;
    }
    if (head != root) {
        result = head->number;
        before_head->next = NULL;
        free(head);
    } else
        free(root);

    return result;
}

void destroy_stack(Stack *root) {
    Stack *previous = NULL;
    while (root) {
        previous = root;
        root = root->next;
        free(previous);
    }
}

int **allocate_matrix() {
    int **matrix = (int **)malloc(25 * sizeof(int *) + 25 * 80 * sizeof(int));
    int *pointer = (int *)(matrix + 25);
    for (int i = 0; i < 25; i++) matrix[i] = pointer + i * 80;

    for (int row = 0; row < 25; row++)
        for (int col = 0; col < 80; col++) matrix[row][col] = 0;

    return matrix;
}
