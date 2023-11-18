#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct node *init(const struct door *door) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp->door = *door;
    tmp->next = NULL;
    return tmp;
}

struct node *add_door(struct node *elem, const struct door *door) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp->door = *door;
    tmp->next = elem->next;
    elem->next = tmp;
    return tmp;
}

struct node *find_door(int door_id, struct node *root) {
    struct node *tmp = root, *pointer = NULL;
    if (root == NULL) return pointer;
    while (tmp->next && tmp->door.id != door_id) {
        pointer = tmp;
        tmp = tmp->next;
    }
    if (tmp->door.id == door_id && tmp->next == NULL && tmp == root) pointer = root;
    return pointer;
}

struct node *remove_door(struct node *elem, struct node *root) {
    struct node *tmp = root;
    struct node *previous_elem = NULL;
    struct node *result;
    find_door(1, root);

    while (tmp && tmp != elem) {
        previous_elem = tmp;
        tmp = tmp->next;
    }

    if (!tmp)
        result = root;
    else if (previous_elem) {
        previous_elem->next = elem->next;
        result = root;
        free(elem);
    } else {
        free(root);
        result = NULL;
    }

    return result;
}

void destroy(struct node *root) {
    struct node *previous = NULL;
    while (root) {
        previous = root;
        root = root->next;
        free(previous);
    }
}