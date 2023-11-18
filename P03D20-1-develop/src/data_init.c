#include <stdio.h>
#include <stdlib.h>

#include "data_structs.h"

Expression_node *init_data() {
    int error = 0;
    Expression_node *infix_expression_root = create_expression_node('r');

    parse_input_to_expression(infix_expression_root, &error);
    if (!error) convert_expression_digits_to_numbers(infix_expression_root);

    if (error) {
        destroy_expression(infix_expression_root);
        infix_expression_root = NULL;
        printf("ERROR: Ivalid expression!");
    }

    return infix_expression_root;
}

void free_data(Expression_node *expression_root, int **matrix) {
    if (expression_root) destroy_expression(expression_root);
    free(matrix);
}
