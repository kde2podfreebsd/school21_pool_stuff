#include "data_process.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structs.h"

void process_data(Expression_node *infix_expression_root, int **matrix) {
    Expression_node *postfix_expression_root = convert_to_postfix(infix_expression_root);

    double step = 4. * M_PI / 79.;
    for (int x_plot = 0; x_plot < 80; x_plot++) {
        double y = calculate_postfix(postfix_expression_root, x_plot * step);
        int y_plot = (int)round(y * 12 + 12);
        if (y_plot >= 0 && y_plot <= 24) matrix[y_plot][x_plot] = 1;
    }
}

Expression_node *convert_to_postfix(Expression_node *infix_root) {
    Expression_node *infix = infix_root;
    Expression_node *postfix_root = create_expression_node('r');
    Stack *stack_root = create_stack_node('r', 0);
    Stack *stack_head = stack_root;

    while (infix) {
        if (infix->lexeme_char == ')') {
            while (stack_head->operation != '(') {
                char operation = pop_from_stack_char(stack_root);
                stack_head = get_head(stack_root);
                push_to_expression(create_expression_node(operation), postfix_root);
            }
            pop_from_stack_char(stack_root);
            stack_head = get_head(stack_root);

        } else if ((infix->lexeme_char - '0' >= 0 && infix->lexeme_char - '0' <= 9) ||
                   infix->lexeme_char == '.' || infix->lexeme_char == 'x') {
            Expression_node *tmp = create_expression_node(infix->lexeme_char);
            tmp->lexeme_number = infix->lexeme_number;
            push_to_expression(tmp, postfix_root);

        } else if (infix->lexeme_char == '(') {
            stack_head = push_to_stack(infix->lexeme_char, 0, stack_root);

        } else {
            if (stack_head == stack_root) {
                stack_head = push_to_stack(infix->lexeme_char, 0, stack_root);

            } else if (get_priority(infix->lexeme_char) > get_priority(stack_head->operation)) {
                stack_head = push_to_stack(infix->lexeme_char, 0, stack_root);

            } else {
                while (stack_head != stack_root &&
                       get_priority(infix->lexeme_char) <= get_priority(stack_head->operation)) {
                    char operation = pop_from_stack_char(stack_root);
                    stack_head = get_head(stack_root);
                    push_to_expression(create_expression_node(operation), postfix_root);
                }

                stack_head = push_to_stack(infix->lexeme_char, 0, stack_root);
            }
        }

        infix = infix->next;
    }

    while (stack_head != stack_root) {
        char operation = pop_from_stack_char(stack_root);
        stack_head = get_head(stack_root);
        push_to_expression(create_expression_node(operation), postfix_root);
    }

    return postfix_root;
}

int get_priority(char ch) {
    int priority = 0;

    /*
      's' - sin
      'c' - cos
      'g' - ctg
      't' - tan
      'l' - ln
      'q' - sqrt
    */
    if (ch == 's' || ch == 'c' || ch == 'g' || ch == 't' || ch == 'l' || ch == 'q')
        priority = 4;
    else if (ch == '*' || ch == '/')
        priority = 3;
    else if (ch == '-' || ch == '+')
        priority = 2;
    else if (ch == '(')
        priority = 1;

    return priority;
}

double calculate_postfix(Expression_node *postfix, double x) {
    Expression_node *lexeme = postfix->next;
    Stack *stack_root = create_stack_node('r', 0);
    double number;

    while (lexeme) {
        if (lexeme->lexeme_char == 'x') {
            number = x;

        } else if ((lexeme->lexeme_char - '0' >= 0 && lexeme->lexeme_char - '0' <= 9) ||
                   lexeme->lexeme_char == '.') {
            number = lexeme->lexeme_number;

        } else if (lexeme->lexeme_char == '-') {
            number = pop_from_stack_double(stack_root);
            Stack *stack_head = get_head(stack_root);
            if (stack_head == stack_root)
                number = -number;
            else {
                number = pop_from_stack_double(stack_root) - number;
            }

        } else if (lexeme->lexeme_char == '+') {
            number = pop_from_stack_double(stack_root);
            number += pop_from_stack_double(stack_root);

        } else if (lexeme->lexeme_char == '*') {
            number = pop_from_stack_double(stack_root);
            number *= pop_from_stack_double(stack_root);

        } else if (lexeme->lexeme_char == '/') {
            number = pop_from_stack_double(stack_root);
            number = pop_from_stack_double(stack_root) / number;

        } else if (lexeme->lexeme_char == 's') {
            number = sin(pop_from_stack_double(stack_root));

        } else if (lexeme->lexeme_char == 'c') {
            number = cos(pop_from_stack_double(stack_root));

        } else if (lexeme->lexeme_char == 'g') {
            number = 1 / tan(pop_from_stack_double(stack_root));

        } else if (lexeme->lexeme_char == 't') {
            number = tan(pop_from_stack_double(stack_root));

        } else if (lexeme->lexeme_char == 'l') {
            number = log(pop_from_stack_double(stack_root));

        } else if (lexeme->lexeme_char == 'q') {
            number = sqrt(pop_from_stack_double(stack_root));
        }

        push_to_stack(' ', number, stack_root);

        lexeme = lexeme->next;
    }

    double y = pop_from_stack_double(stack_root);

    destroy_stack(stack_root);
    return y;
}
