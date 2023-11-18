#ifndef DATA_PROCESS_H
#define DATA_PROCESS_H

#include <math.h>

#include "data_structs.h"

void process_data(Expression_node *infix_expression_root, int **matrix);

Expression_node *convert_to_postfix(Expression_node *infix_expression_root);
int get_priority(char ch);
double calculate_postfix(Expression_node *postfix, double x);

#endif
