#include <stdio.h>

#define N 15
#define M 13

// void transform(int data[N][M], int** matrix, int n);
void make_picture(int** picture, int n, int m);
void reset_picture(int** picture, int n, int m);
void print_picture(int** picture, int n, int m);

int main() {
    const int picture_data[N][M];
    int** picture;
    int* pointers[N];
    for (int i = 0; i < N; i++) pointers[i] = (int*)picture_data[i];
    picture = pointers;

    //  transform(picture_data, picture, N);

    make_picture(picture, N, M);

    print_picture(picture, N, M);

    return 0;
}

void make_picture(int** picture, int n, int m) {
    int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int tree_trunk[] = {7, 7, 7, 7};
    int tree_foliage[] = {3, 3, 3, 3};
    int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                          {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    reset_picture(picture, n, m);

    int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);
    for (int i = 0; i < length_frame_w; i++) {
        picture[0][i] = frame_w[i];
        picture[N / 2][i] = frame_w[i];
        picture[N - 1][i] = frame_w[i];
    }

    int length_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);
    for (int i = 0; i < length_frame_h; i++) {
        picture[i][0] = frame_h[i];
        picture[i][M / 2] = frame_h[i];
        picture[i][M - 1] = frame_h[i];
    }

    int length_tree_trunk = sizeof(tree_trunk) / sizeof(tree_trunk[0]);
    for (int i = 0; i < length_tree_trunk; i++) {
        picture[7 - i == 7 ? 6 + i : 7 + i][3] = tree_trunk[i];
        picture[7 - i == 7 ? 6 + i : 7 + i][4] = tree_trunk[i];
        picture[10][2 + i] = tree_trunk[i];
    }

    int length_tree_foliage = sizeof(tree_foliage) / sizeof(tree_foliage[0]);
    for (int i = 0; i < length_tree_foliage; i++) {
        picture[2 + i][3] = tree_foliage[i];
        picture[2 + i][4] = tree_foliage[i];
        picture[3][2 + i] = tree_foliage[i];
        picture[4][2 + i] = tree_foliage[i];
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            picture[1 + i][7 + j] = sun_data[i][j];
        }
    }
}

void reset_picture(int** picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

// void transform(int data[N][M], int** matrix, int n) {
//     for (int i = 0; i < n; i++) matrix[i] = data[i];
// }

void print_picture(int** picture, int n, int m) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            printf("%d", picture[row][col]);
            if (col != m - 1) printf(" ");
        }
        if (row != n - 1) printf("\n");
    }
}