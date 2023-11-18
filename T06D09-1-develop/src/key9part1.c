/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

#define NMAX 10

void input(int *buffer, int *length, int *error);
void output(int *buffer, int length);
int sum_numbers(const int *buffer, int length);
int find_numbers(const int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int n, data[NMAX];
    int error = 0;

    input(data, &n, &error);

    if (!error) {
        int sum = sum_numbers(data, n);
        if (sum) {
            int numbers[NMAX] = {0};
            int count = find_numbers(data, n, sum, numbers);
            if (count) {
                printf("%d\n", sum);
                output(numbers, count);
            } else
                printf("n/a");
        } else
            printf("n/a");
    } else
        printf("n/a");

    return 0;
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(const int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0 && buffer[i] != 0) {
            sum += buffer[i];
        }
    }

    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(const int *buffer, int length, int number, int *numbers) {
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[j] = buffer[i];
            j++;
        }
    }
    return j;
}

void input(int *buffer, int *length, int *error) {
    if (!scanf("%d", length) || *length <= 0 || *length > 10) {
        *error = 1;
    } else {
        for (int i = 0; i < *length; i++) {
            if (!scanf("%d", &buffer[i])) {
                *error = 1;
                break;
            }
        }
    }
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i != length - 1) printf(" ");
    }
}
