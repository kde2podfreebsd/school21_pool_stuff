#include "list.h"

#include <stdio.h>

#include "door_struct.h"

char *add_door_test(struct node *list_elem, struct door *new_door);
char *remove_door_test(struct node *list_elem, struct node *root);

int main() {
#ifdef LIST_ADD_REMOVE_TEST
    struct door door_1, door_2;
    door_1.id = 1;
    door_2.id = 2;
    door_1.status = 0;
    door_2.status = 0;
    struct node *door_list_1 = init(&door_1);
    char *result;

    result = add_door_test(door_list_1, &door_2);
    printf("%s\n", result);
    result = remove_door_test(door_list_1->next, door_list_1);
    printf("%s", result);

    destroy(door_list_1);
#endif

    return 0;
}

char *add_door_test(struct node *list_elem, struct door *new_door) {
    char *result = "FAIL";
    struct node *added_list_elem = add_door(list_elem, new_door);
    if (list_elem->next == added_list_elem && added_list_elem->door.id == new_door->id) result = "SUCCESS";
    return result;
}

char *remove_door_test(struct node *list_elem, struct node *root) {
    char *result = "FAIL";
    struct node *returned_elem = remove_door(list_elem, root);
    if (returned_elem == root) result = "SUCCESS";
    return result;
}