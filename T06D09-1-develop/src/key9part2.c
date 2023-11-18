#include <stdio.h>

#define LEN 100

int input_array_number(int *buffer, int *error);
void output(const int *buffer, int length);
int sum(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length);
int sub(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length);
void reset_result(int *buffer, int length);
void cycle_shift(int *buffer, int length, int shift);
int check_arrays_equality(const int *a, int len1, const int *b, int len2);

int main() {
    int len1, len2, number1[LEN] = {0}, number2[LEN] = {0};
    int error = 0;
    len1 = input_array_number(number1, &error);
    if (!error) len2 = input_array_number(number2, &error);

    if (!error) {
        if (!(len2 > len1)) {
            int over, equality;
            int lenr = 0, result[LEN] = {0};

            cycle_shift(number1, LEN, len1 - LEN);
            cycle_shift(number2, LEN, len2 - LEN);

            over = sum(number1, len1, number2, len2, result, &lenr);
            cycle_shift(result, LEN, -lenr);
            if (over) printf("1 ");
            output(result, lenr);
            printf("\n");

            reset_result(result, lenr);
            equality = check_arrays_equality(number1, LEN, number2, LEN);
            over = sub(number1, len1, number2, len2, result, &lenr);
            if (equality)
                printf("0");
            else if (!over) {
                cycle_shift(result, LEN, -lenr);
                output(result, lenr);
            } else
                printf("n/a");
        } else
            printf("n/a");
    } else
        printf("n/a");

    return 0;
}

int input_array_number(int *buffer, int *error) {
    char digit, ch = ' ';
    int length = 0;
    int unmeaning_zeros = 1;

    do {
        scanf("%c%c", &digit, &ch);
        buffer[length] = digit - '0';
        if (buffer[length] < 0 || buffer[length] > 9) *error = 1;
        if (unmeaning_zeros && buffer[length]) unmeaning_zeros = 0;
        if (!unmeaning_zeros) length++;
    } while (ch == ' ' && length != LEN);

    if ((length == LEN && ch != '\n') || (length < LEN && ch != ' ' && ch != '\n')) *error = 1;
    if (unmeaning_zeros && !length) length = 1;

    return length;
}

void output(const int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i != length - 1) printf(" ");
    }
}

void reset_result(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        buffer[i] = 0;
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void cycle_shift_left(int *buffer, int length) {
    int tmp = buffer[0];
    for (int i = 1; i < length; i++) {
        swap(&buffer[i - 1], &buffer[i]);
    }
    buffer[length - 1] = tmp;
}

void cycle_shift(int *buffer, int length, int shift) {
    for (int i = 1; i <= (shift < 0 ? length + shift : shift); i++) {
        cycle_shift_left(buffer, length);
    }
}

int sum(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length) {
    *result_length = 0;
    int i = LEN - 1;
    int tmp = 0;

    while (i >= LEN - len2 || i >= LEN - len1 || (tmp == 1 && i < LEN - len1 && i != -1)) {
        int s = buff1[i] + buff2[i] + tmp;
        if (s > 9) {
            s = s - 10;
            tmp = 1;
        } else {
            tmp = 0;
        }
        result[i] = s;
        *result_length += 1;
        i--;
    }

    if (!*result_length) *result_length = 1;
    return i == -1 && tmp == 1;
}

int sub(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length) {
    *result_length = 0;
    int i = LEN - 1;
    int tmp = 0;

    while (i >= LEN - len2 || i >= LEN - len1 || (tmp == 1 && i < LEN - len1 && i != -1)) {
        int s = buff1[i] - buff2[i] - tmp;
        if (s < 0) {
            s = s + 10;
            tmp = 1;
        } else {
            tmp = 0;
        }
        result[i] = s;
        *result_length += 1;
        i--;
    }

    if (result[i + 1] == 0) *result_length -= 1;
    if (!*result_length) *result_length = 1;
    return i == -1 && tmp == 1;
}

int check_arrays_equality(const int *a, int len1, const int *b, int len2) {
    int check = 1;

    if (len1 != len2)
        check = 0;
    else {
        for (int i = 0; i < len1; i++) {
            if (a[i] != b[i]) {
                check = 0;
                break;
            }
        }
    }

    return check;
}