#include <stdio.h>
#include <stdlib.h>

int main() {
    char string[100];

    int i = 0;
    char temp = getchar();
    string[i] = temp;
    while (temp != '\n') {
        i++;
        temp = getchar();
        string[i] = temp;
    }

    char n1[i / 2];
    char n2[i / 2];

    for (int k = 0; k < i / 2; k++) {
        n1[k] = string[k];
    }

    for (int k = i - 1, j = 0; k >= i / 2; k--, j++) {
        n2[j] = string[k];
    }

    for (int j = 0; j < i / 2; j++) {
        if (n1[j] != n2[j]) {
            printf("NO\n");
            return 1;
        }
    }

    printf("YES\n");

    return 0;
}