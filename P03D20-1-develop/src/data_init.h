#ifndef DATA_INIT_H
#define DATA_INIT_H

#include "data_structs.h"

Expression_node *init_data();
void free_data(Expression_node *expression_root, int **matrix);

#endif
