#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_init.h"
#include "data_plot.h"
#include "data_process.h"
#include "data_structs.h"

int main() {
    int **matrix = allocate_matrix();

    Expression_node *infix_expression_root = init_data();
    process_data(infix_expression_root, matrix);
    make_plot(matrix);
    free_data(infix_expression_root, matrix);

    return 0;
}