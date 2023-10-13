#include <stdio.h>
#include <stdlib.h>

void input(int **buffer, int *length);
void output(int *buffer, int length);

int main() {
    int *buffer = NULL;
    int length;
    input(&buffer, &length);
    output(buffer, length);
    free(buffer);
    return 0;
}

void input(int **buffer, int *length) {
    scanf("%d", length);
    *buffer = (int *)malloc(*length * sizeof(int));

    if (*buffer == NULL) {
        exit(1);
    }

    for (int i = 0; i < *length; i++) {
        scanf("%d", &(*buffer)[i]);
    }
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", buffer[i]);
    }
}

