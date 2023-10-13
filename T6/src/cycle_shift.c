#include <stdio.h>

#define customAbs(x) ((x < 0) ? -(x) : (x))

int input(int *a, int arr_size, int *shift);
void output(int *a, int arr_size);
void cyclicShiftLeft(int *arr, int n, int shift);
void cyclicShiftRight(int *arr, int n, int shift);

int main(void){
    int arr_size;
    int shift;
    char garbage;
    if(scanf("%d%c", &arr_size, &garbage) == 2 && garbage == '\n'){
        int array[arr_size];
        if(input(array, arr_size, &shift) == 1){
        printf("n/a");
        return 1;
    }

    (shift >= 0) ? cyclicShiftLeft(array, arr_size, shift) : cyclicShiftRight(array, arr_size, shift);

    output(array, arr_size);

    return 0;

    } else{
        printf("n/a");
        return 1;
    }
}

int input(int *a, int arr_size, int *shift){
    char garbage;
    for(int *p = a; p - a < arr_size; p++){
        if(scanf("%d%c", p, &garbage) == 2 && garbage == '\n'){} else {
            return 1;
        }
    }

    if(scanf("%d%c", shift, &garbage) == 2 && garbage == '\n'){} else {
            return 1;
    }

    return 0;
}

void output(int *a, int arr_size){
    for(int *p = a; p - a < arr_size; p++){
        printf("%d ", *p);
    }
}

void cyclicShiftLeft(int *arr, int n, int shift) {
    shift = shift % n;
    for (int i = 0; i < shift; i++) {
        int temp = arr[0];
        for (int j = 0; j < n - 1; j++) {
            arr[j] = arr[j + 1];
        }
        arr[n - 1] = temp;
    }
}

void cyclicShiftRight(int *arr, int n, int shift){
    shift = shift % n;
    for (int i = 0; i < customAbs(shift); i++){
        int temp = arr[n-1];
        for (int j = n-1; j > 0; j--) {
            arr[j] = arr[j - 1];
        }
        arr[0] = temp;
    }
}
