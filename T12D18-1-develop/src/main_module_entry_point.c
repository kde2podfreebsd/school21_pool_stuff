#include <stdio.h>

#include "documentation_module.h"
#include "print_module.h"

void output_availability(Node *list_root);

int main() {
#ifdef PRINT_MODULE
    print_log(print_char, Module_load_success_message);
#endif

#ifdef DOCUMENTATION_MODULE
    Node *availability_list_root = check_available_documentation_module(validate, Documents_count, Documents);
    output_availability(availability_list_root);
    destroy(availability_list_root);
#endif
    return 0;
}