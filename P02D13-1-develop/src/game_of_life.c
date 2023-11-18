#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIELD_SIZE_X 80
#define FIELD_SIZE_Y 25
#define INITIAL_SPEED 500000
#define MAX_SPEED 500
#define MIN_SPEED 500000

#define TRUE 1
#define FALSE 0

int **init(int argc, char **argv, int *speed, int *no_delay);
void play_game_of_life(int **matrix, int *speed, int *no_delay);
void finish(int **matrix);

void use_controls(int *speed, int *no_delay, int is_started, int **matrix);
void calculate_next_step(int **currentStep, int **nextStep);
void make_next_step(int **currentStep, int **nextStep);
int is_game_ended(int **currentStep, int **nextStep);
void draw_field(int **currentStep, int speed, int epoch);

int **allocate_matrix(int rows, int cols);
void copy_matrix(int **matrix_from, int **matrix_to);
void reset_matrix(int **matrix);
void read_preset_stdin(int **matrix);
void set_random_state(int **matrix);

void handle_mouse_button_1_click(MEVENT event, int **matrix, int *speed);

int main(int argc, char **argv) {
    int speed, no_delay = FALSE;

    int **data = init(argc, argv, &speed, &no_delay);
    play_game_of_life(data, &speed, &no_delay);
    finish(data);

    return 0;
}

int **init(int argc, char **argv, int *speed, int *no_delay) {
    int **data = allocate_matrix(FIELD_SIZE_Y, FIELD_SIZE_X);
    *speed = INITIAL_SPEED;

    if (argc >= 2) {
        if (argv[1][0] == 'p') read_preset_stdin(data);
    }

    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, *no_delay);
    keypad(stdscr, TRUE);

    draw_field(data, *speed, 0);
    printw("Press Spacebar to start...\n");
    refresh();

    mousemask(BUTTON1_CLICKED, NULL);
    use_controls(speed, no_delay, FALSE, data);

    return data;
}

void finish(int **matrix) {
    printw("The Game is ended. Closing application...\n");
    refresh();
    sleep(5);

    free(matrix);
    clear();
    refresh();
    endwin();
}

void play_game_of_life(int **matrix, int *speed, int *no_delay) {
    int epoch = 0;
    int **currentStep = matrix;
    int **nextStep = allocate_matrix(FIELD_SIZE_Y, FIELD_SIZE_X);
    calculate_next_step(currentStep, nextStep);

    while (!is_game_ended(currentStep, nextStep)) {
        make_next_step(currentStep, nextStep);
        epoch++;

        draw_field(currentStep, *speed, epoch);
        use_controls(speed, no_delay, TRUE, matrix);

        calculate_next_step(currentStep, nextStep);
        usleep(*speed);
    }

    free(nextStep);
}

int is_game_ended(int **currentStep, int **nextStep) {
    int is_ended = TRUE;

    for (int row = 0; row < FIELD_SIZE_Y; row++) {
        for (int col = 0; col < FIELD_SIZE_X; col++) {
            if (currentStep[row][col] != nextStep[row][col]) {
                is_ended = FALSE;
            }
        }
    }

    return is_ended;
}

void calculate_next_step(int **currentStep, int **nextStep) {
    int near_population;

    for (int row = 0; row < FIELD_SIZE_Y; row++) {
        for (int col = 0; col < FIELD_SIZE_X; col++) {
            near_population = 0;
            near_population += currentStep[row - 1 < 0 ? FIELD_SIZE_Y - 1 : row - 1]
                                          [col - 1 < 0 ? FIELD_SIZE_X - 1 : col - 1];
            near_population += currentStep[row - 1 < 0 ? FIELD_SIZE_Y - 1 : row - 1][col];
            near_population += currentStep[row - 1 < 0 ? FIELD_SIZE_Y - 1 : row - 1]
                                          [col + 1 > FIELD_SIZE_X - 1 ? 0 : col + 1];
            near_population += currentStep[row][col - 1 < 0 ? FIELD_SIZE_X - 1 : col - 1];
            near_population += currentStep[row][col + 1 > FIELD_SIZE_X - 1 ? 0 : col + 1];
            near_population += currentStep[row + 1 > FIELD_SIZE_Y - 1 ? 0 : row + 1]
                                          [col - 1 < 0 ? FIELD_SIZE_X - 1 : col - 1];
            near_population += currentStep[row + 1 > FIELD_SIZE_Y - 1 ? 0 : row + 1][col];
            near_population += currentStep[row + 1 > FIELD_SIZE_Y - 1 ? 0 : row + 1]
                                          [col + 1 > FIELD_SIZE_X - 1 ? 0 : col + 1];

            if (!currentStep[row][col] && near_population == 3) nextStep[row][col] = 1;
            if (currentStep[row][col] && (near_population < 2 || near_population > 3)) nextStep[row][col] = 0;
            if (currentStep[row][col] && near_population >= 2 && near_population <= 3) nextStep[row][col] = 1;
        }
    }
}

void make_next_step(int **currentStep, int **nextStep) {
    copy_matrix(nextStep, currentStep);
    reset_matrix(nextStep);
}

void copy_matrix(int **matrix_from, int **matrix_to) {
    for (int row = 0; row < FIELD_SIZE_Y; row++) {
        for (int col = 0; col < FIELD_SIZE_X; col++) {
            matrix_to[row][col] = matrix_from[row][col];
        }
    }
}

void set_random_state(int **matrix) {
    for (int row = 0; row < FIELD_SIZE_Y; row++) {
        for (int col = 0; col < FIELD_SIZE_X; col++) {
            matrix[row][col] = rand() % 2;
        }
    }
}
void reset_matrix(int **matrix) {
    for (int row = 0; row < FIELD_SIZE_Y; row++) {
        for (int col = 0; col < FIELD_SIZE_X; col++) {
            matrix[row][col] = 0;
        }
    }
}

void use_controls(int *speed, int *no_delay, int is_started, int **matrix) {
    int pressed_key;

    pressed_key = getch();

    if (!is_started && pressed_key != ' ')
        while (pressed_key != ' ') {
            MEVENT event;

            if (pressed_key == 'r' || pressed_key == 'R') {
                set_random_state(matrix);
                draw_field(matrix, *speed, 0);
            }

            if (pressed_key == KEY_MOUSE && getmouse(&event) == OK) {
                handle_mouse_button_1_click(event, matrix, speed);
            }
            pressed_key = getch();
        }

    if (is_started && pressed_key == '+' && *speed >= MAX_SPEED) *speed /= 2;
    if (is_started && pressed_key == '-' && *speed <= MIN_SPEED) *speed *= 2;
    if (pressed_key == ' ') {
        if (*no_delay) {
            nodelay(stdscr, FALSE);
            *no_delay = FALSE;
        } else {
            nodelay(stdscr, TRUE);
            *no_delay = TRUE;
        }
    }
}

int **allocate_matrix(int rows, int cols) {
    int **matrix = malloc(rows * cols * sizeof(int) + rows * sizeof(int *));
    int *pointer = (int *)(matrix + rows);
    for (int row = 0; row < rows; row++) {
        matrix[row] = pointer + row * cols;
    }
    for (int i = 0; i < rows * cols - 1; i++) matrix[i / cols][i % cols] = 0;
    return matrix;
}

void read_preset_stdin(int **matrix) {
    int points_count, x, y;
    scanf("%d", &points_count);

    for (int i = 1; i <= points_count; i++) {
        scanf("%d %d", &x, &y);
        matrix[y][x] = 1;
    }

    while (fgetc(stdin) != EOF) {
    }
    if (!freopen("/dev/tty", "r", stdin)) {
        perror("/dev/tty");
        exit(1);
    }
}

void draw_field(int **currentStep, int speed, int epoch) {
    char vert_border = '|';
    char horiz_border = '-';
    char dead = ' ';
    char alive = '*';

    clear();
    printw("Controls: '+' - increase speed, '-' - decrease speed\n");
    printw("' '(Spacebar) - start game, 'R' - random initial state\n");
    printw("Current speed: %.1lf\n", INITIAL_SPEED / (double)speed);
    printw("Epoch: %d\n", epoch);
    for (int y = 0; y <= (FIELD_SIZE_Y + 1); y++) {
        for (int x = 0; x <= (FIELD_SIZE_X + 1); x++) {
            if (y == 0 || y == (FIELD_SIZE_Y + 1))
                printw("%c", horiz_border);
            else if (x == 0 || x == (FIELD_SIZE_X + 1))
                printw("%c", vert_border);
            else if (currentStep[y - 1][x - 1])
                printw("%c", alive);
            else
                printw("%c", dead);
        }
        printw("\n");
    }
    refresh();
}

void handle_mouse_button_1_click(MEVENT event, int **matrix, int *speed) {
    if (event.bstate && BUTTON1_CLICKED) {
        if (event.y - 5 >= 0 && event.y - 5 <= FIELD_SIZE_Y - 1 && event.x - 1 >= 0 &&
            event.x - 1 <= FIELD_SIZE_X - 1) {
            matrix[event.y - 5][event.x - 1] = !matrix[event.y - 5][event.x - 1];
            draw_field(matrix, *speed, 0);
            refresh();
        }
    }
}
