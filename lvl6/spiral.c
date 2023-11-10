// #include <stdio.h>
// #include <stdlib.h>

// void allocate(int*** arr, int n, int m) {
//     (*arr) = (int**)malloc(sizeof(int*) * n);
//     for (int i = 0; i < n; ++i) {
//         (*arr)[i] = (int*)malloc(sizeof(int) * m);
//     }
// }

// void freeMem(int*** arr, int n) {
//     for (int i = 0; i < n; ++i) {
//         free((*arr)[i]);
//     }

//     free(*arr);
// }

// int main() {
//     int** arr;
//     int n;
//     scanf("%d", &n);
//     allocate(&arr, n, n);

//     int top = 0;
//     int left = 0;
//     int bottom = n - 1;
//     int right = n - 1;
//     int dir = 0;
//     int iterator = 2;

//     while (top <= bottom && left <= right) {
//         if (dir == 0) {
//             for (int i = left; i <= right; i++) {
//                 arr[top][i] = iterator;
//                 iterator++;
//             }
//             top++;
//         } else if (dir == 1) {
//             for (int i = top; i <= bottom; i++) {
//                 arr[i][right] = iterator;
//                 iterator++;
//             }
//             right--;
//         } else if (dir == 2) {
//             for (int i = right; i >= left; i--) {
//                 arr[bottom][i] = iterator;
//                 iterator++;
//             }
//             bottom--;
//         } else if (dir == 3) {
//             for (int i = bottom; i >= top; i--) {
//                 arr[i][left] = iterator;
//                 iterator++;
//             }
//             left++;
//         }

//         dir = (dir + 1) % 4;
//     }

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             printf("%d ", arr[i][j]);
//         }
//         printf("\n");
//     }

//     freeMem(&arr, n);
//     return 0;
// }



#include <stdio.h>
#include <stdlib.h>

void allocte(int*** arr, int n, int m){
    *arr = malloc(sizeof(int*) * n);
    for(int i = 0; i < n; ++i){
        (*arr)[i] = malloc(sizeof(int) * m);
    }
}

void freeMem(int*** arr, int n){
    for(int i = 0; i < n; ++i){
        free((*arr)[i]);
    }

    free(*arr);
}

int main(){
    int n;
    int** arr;
    scanf("%d", &n);
    allocte(&arr, n, n);

    int left = 0;
    int top = 0;
    int bot = n - 1;
    int right = n - 1;
    int iter = 1;
    int dir = 0;

    while(left <= right && top <= bot){
        if(dir==0){
            for(int i = left; i <= right; ++i){
                arr[top][i] = iter*iter;
                iter++;
                // iter *= iter;
            }
            top++;
        } else if(dir == 1){
            for(int i = top; i <= bot; ++i){
                arr[i][right] = iter*iter;
                iter++;
                // iter *= iter;
            }
            right--;
        } else if(dir == 2){
            for(int i = right; i >= left; i--){
                arr[bot][i] = iter*iter;
                iter++;
                // iter *= iter;
            }
            bot--;
        } else if(dir == 3){
            for(int i = bot; i >= top; i--){
                arr[i][left] = iter*iter;
                iter++;
                // iter *= iter;
            }
            left++;
        }

        dir++;
        dir = dir%4;
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            printf("%d", arr[i][j]);
            if(j < n -1){
                printf(" ");
            }
        }
        if(i < n -1){
            printf("\n");
        }
    }


    freeMem(&arr, n);
}