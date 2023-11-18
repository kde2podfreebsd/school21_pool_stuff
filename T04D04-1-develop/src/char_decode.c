#include <stdio.h>

void encode_stdin();
void decode_stdin();

int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (*argv[1] == '0')
            encode_stdin();
        else if (*argv[1] == '1') {
            decode_stdin();
        } else
            printf("n/a");
    } else
        printf("n/a");

    return 0;
}

void encode_stdin() {
    char ch1, ch2;
    while (1) {
        scanf("%c%c", &ch1, &ch2);

        if (ch2 == '\n') {
            printf("%02X", ch1);
            break;
        }

        if (ch2 != ' ') {
            printf("n/a");
            return;
        }

        printf("%02X ", ch1);
    }
}

void decode_stdin() {
    char ch1, ch2, ch3;
    while (1) {
        scanf("%c%c%c", &ch1, &ch2, &ch3);

        int digit1;
        if (ch1 >= '0' && ch1 <= '9')
            digit1 = ch1 - '0';
        else if (ch1 >= 'A' && ch1 <= 'F')
            digit1 = ch1 - 'A' + 10;
        else {
            printf("n/a");
            return;
        }

        int digit2;
        if (ch2 >= '0' && ch2 <= '9')
            digit2 = ch2 - '0';
        else if (ch2 >= 'A' && ch2 <= 'F')
            digit2 = ch2 - 'A' + 10;
        else {
            printf("n/a");
            return;
        }

        int number = digit1 * 16 + digit2;

        if (ch3 == '\n') {
            printf("%c", number);
            break;
        }

        if (ch3 != ' ') {
            printf("n/a");
            return;
        }

        printf("%c ", number);
    }
}