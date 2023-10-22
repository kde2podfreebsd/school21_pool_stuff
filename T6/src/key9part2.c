// NOT WORKING!


#include <stdio.h>

#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void printNumber(int *num, int length);
void reverseNumber(int *num, int length);

int main()
{
    int buff1[LEN] = {9, 9, 9};
    int buff2[LEN] = {9, 9, 1};
    int result[LEN];
    int result_length;

    sum(buff1, 3, buff2, 3, result, &result_length);
    printf("Sum: ");
    printNumber(result, result_length);
}

void printNumber(int *num, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", num[i]);
    }
    printf("\n");
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int carry = 0;
    *result_length = len1 > len2 ? len1 : len2;

    for (int i = 0; i < *result_length; i++) {
        int digit1 = (i < len1) ? buff1[i] : 0;
        int digit2 = (i < len2) ? buff2[i] : 0;

        int sum = digit1 + digit2 + carry;
        if (sum >= 10) {
            carry = 1;
            sum -= 10;
        } else {
            carry = 0;
        }

        result[i] = sum;
    }

    if (carry > 0) {
        result[*result_length] = carry;
        (*result_length)++;
    }
}