#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

typedef struct expression_node {
    char lexeme_char;
    double lexeme_number;
    struct expression_node *next;
} Expression_node;

Expression_node *create_expression_node(char lexeme);
void push_to_expression(Expression_node *node, Expression_node *root);
void destroy_expression(Expression_node *root);

void parse_input_to_expression(Expression_node *root, int *error);
void convert_expression_digits_to_numbers(Expression_node *root);

typedef struct stack {
    char operation;
    double number;
    struct stack *next;
} Stack;

Stack *create_stack_node(char operation, double number);
Stack *get_head(Stack *root);
Stack *push_to_stack(char operation, double number, Stack *root);
char pop_from_stack_char(Stack *root);
double pop_from_stack_double(Stack *root);
void destroy_stack(Stack *root);

int **allocate_matrix();

#endif
