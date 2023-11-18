#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door *doors);
void sort_ascending(struct door *doors);
void swap(struct door *door_a, struct door *door_b);
void output(struct door *doors);
void reset_doors_status(struct door *doors);

int main() {
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);
    sort_ascending(doors);
    reset_doors_status(doors);
    output(doors);

    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door *doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void sort_ascending(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT - 1; i++) {
        for (int j = i; j < DOORS_COUNT; j++) {
            if (doors[i].id > doors[j].id) swap(&doors[i], &doors[j]);
        }
    }
}

void swap(struct door *door_a, struct door *door_b) {
    struct door tmp = *door_a;
    *door_a = *door_b;
    *door_b = tmp;
}

void output(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        printf("%d, %d", doors[i].id, doors[i].status);
        if (i != DOORS_COUNT - 1) printf("\n");
    }
}

void reset_doors_status(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].status = 0;
    }
}