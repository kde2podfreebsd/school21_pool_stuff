// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

#define FIELD_SIZE_X 80
#define FIELD_SIZE_Y 25
#define RACKET_SIZE 3
#define BALL_SIZE 1
#define WIN_CONDITION 21
#define PI 3.14159265358979323846
#define ANGLE 29.4
#define INITIAL_SPEED 1

void print_start_screen();
void play_pong();

double to_radians(double degrees);
double power(double base, int exponent);
double factorial(int number);
double sin_deg(double degrees);
double cos_deg(double degrees);

void update_screen(int start_screen_flag, int score_p1, int score_p2, int ball_x1, int ball_y1,
                   int racket_p1_y, int racket_p2_y);
void print_pong();
void clear_screen();

int move_racket(int player, int racket_y);

int main() {
    print_start_screen();
    play_pong();
    return 0;
}

void print_start_screen() {
    clear_screen();
    update_screen(1, 21, 0, FIELD_SIZE_X / 2 + 1, FIELD_SIZE_Y / 2 + 1, FIELD_SIZE_Y / 2 - 1,
                  FIELD_SIZE_Y / 2 - 1);
}

void play_pong() {
    int score_p1 = 0, score_p2 = 0;
    int speed = INITIAL_SPEED;
    while (score_p1 < WIN_CONDITION && score_p2 < WIN_CONDITION) {
        int racket_p1_y, racket_p2_y;
        racket_p1_y = racket_p2_y = FIELD_SIZE_Y / 2 - 1;
        double ball_x1 = FIELD_SIZE_X / 2. + 1;
        double ball_y1 = FIELD_SIZE_Y / 2.;
        int ball_dir_y = 1, ball_dir_x = 1;
        while (ball_x1 >= 3 && ball_x1 <= FIELD_SIZE_X - 2) {
            double ball_x2 = ball_x1 + ball_dir_x * speed * cos_deg(ANGLE);
            double ball_y2 = ball_y1 + ball_dir_y * speed * sin_deg(ANGLE);
            if (ball_y2 < 1) {
                ball_y2 = 2 - ball_y2;
                ball_dir_y = -ball_dir_y;
            }
            if (ball_y2 > FIELD_SIZE_Y) {
                ball_y2 = FIELD_SIZE_Y * 2 - ball_y2;
                ball_dir_y = -ball_dir_y;
            }
            double y_l_cross = ball_dir_y * sin_deg(ANGLE) / cos_deg(ANGLE) * (3 - ball_x1) + ball_y1;
            double y_r_cross =
                ball_dir_y * sin_deg(ANGLE) / cos_deg(ANGLE) * (FIELD_SIZE_X - 2 - ball_x1) + ball_y1;
            if (ball_x2 <= 3 && y_l_cross >= racket_p1_y && y_l_cross <= racket_p1_y + 2) {
                ball_x2 = 3 * 2 - ball_x2;
                ball_dir_x = -ball_dir_x;
            }
            if (ball_x2 >= FIELD_SIZE_X - 2 && y_r_cross >= racket_p2_y && y_r_cross <= racket_p2_y + 2) {
                ball_x2 = (FIELD_SIZE_X - 2) * 2 - ball_x2;
                ball_dir_x = -ball_dir_x;
            }
            ball_y1 = ball_y2;
            ball_x1 = ball_x2;
            update_screen(0, score_p1, score_p2, ball_x1, ball_y1, racket_p1_y, racket_p2_y);
            racket_p1_y = move_racket(1, racket_p1_y);
            racket_p2_y = move_racket(2, racket_p2_y);
        }
        if (ball_x1 < 2)
            score_p2 += 1;
        else
            score_p1 += 1;
    }
    update_screen(0, score_p1, score_p2, FIELD_SIZE_X / 2 + 1, FIELD_SIZE_Y / 2 + 1, FIELD_SIZE_Y / 2 - 1,
                  FIELD_SIZE_Y / 2 - 1);
    if (score_p1 == WIN_CONDITION)
        printf("Player 1 WON!!! Congratulations!\n");
    else
        printf("Player 2 WON!!! Congratulations!\n");
}

int move_racket(int player, int racket_y) {
    char action_player;
    int racket_y_2 = racket_y;
    printf("Player %d enter action:\n", player);

    char control_up, control_down;
    if (player == 1)
        control_up = 'A';
    else
        control_up = 'K';
    if (player == 1)
        control_down = 'Z';
    else
        control_down = 'M';

    do {
        do {
            action_player = getchar();
        } while (action_player != '\n');
        action_player = getchar();
        if (action_player == ' ')
            break;
        else if (action_player == control_up && racket_y >= 2)
            racket_y_2 -= 1;
        else if (action_player == control_down && racket_y <= FIELD_SIZE_Y - RACKET_SIZE)
            racket_y_2 += 1;
        else
            printf("Wrong command\n");
    } while (action_player != ' ' && action_player != control_up && action_player != control_down);
    return racket_y_2;
}

void print_pong() {
    for (int i = 0; i <= FIELD_SIZE_X + 1; i++) printf("-");
    printf("\n");
    printf("|               ##########     ########     #          #     ########            |\n");
    printf("|              #          #   #        #    # #        #    #        #           |\n");
    printf("|              #          #   #        #    #  #       #    #                    |\n");
    printf("|              #          #   #        #    #   #      #    #                    |\n");
    printf("|              ###########    #        #    #    #     #    #                    |\n");
    printf("|              #              #        #    #     #    #    #   #####            |\n");
    printf("|              #              #        #    #      #   #    #        #           |\n");
    printf("|              #              #        #    #       #  #    #        #           |\n");
    printf("|              #              #        #    #        # #    #        #           |\n");
    printf("|              #               ########     #          #     ########            |\n");
}

void clear_screen() {
    printf("\n");
    printf("\33c\e[3J");
}

void update_screen(int start_screen_flag, int score_p1, int score_p2, int ball_x1, int ball_y1,
                   int racket_p1_y, int racket_p2_y) {
    clear_screen();
    print_pong();

    char ch;
    printf("| Player1                                                                Player2 |\n");
    printf("| UP - A, DOWN - Z, ' ' - skip        %2d : %-2d       UP - K, DOWN - M, ' ' - skip |\n",
           score_p1, score_p2);
    for (int x = 0; x <= FIELD_SIZE_X + 1; x++) printf("-");
    printf("\n");

    for (int y = 1; y <= FIELD_SIZE_Y; y++) {
        printf("|");
        for (int x = 1; x <= FIELD_SIZE_X; x++) {
            if (y >= racket_p1_y && y <= racket_p1_y + (RACKET_SIZE - 1) && x == 3)
                printf("|");
            else if (y >= racket_p2_y && y <= racket_p2_y + (RACKET_SIZE - 1) && x == FIELD_SIZE_X - 2)
                printf("|");
            else if (y == ball_y1 && x == ball_x1)
                printf("*");
            else if (x == FIELD_SIZE_X / 2 + 1)
                printf("|");
            else
                printf(" ");
        }
        printf("|\n");
    }

    for (int i = 0; i <= FIELD_SIZE_X + 1; i++) printf("-");
    printf("\n");

    if (start_screen_flag) {
        printf("Press Enter to start the game: ");
        scanf("%c", &ch);
    }

    printf("\n");
}

double to_radians(double degrees) { return degrees * PI / 180.0; }

double power(double base, int exponent) {
    double result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

double factorial(int number) {
    double result = 1;

    for (int i = 1; i <= number; i++) {
        result *= i;
    }

    return result;
}

double sin_deg(double degrees) {
    double radians = to_radians(degrees);
    double result = radians;
    int sign = -1;
    int power_index = 3;

    for (int i = 0; i < 5; i++) {
        result += (sign * power(radians, power_index)) / factorial(power_index);
        sign *= -1;
        power_index += 2;
    }

    return result;
}

double cos_deg(double degrees) {
    double radians = to_radians(degrees);
    double result = 1;
    int sign = -1;
    int power_index = 2;

    for (int i = 0; i < 5; i++) {
        result += (sign * power(radians, power_index)) / factorial(power_index);
        sign *= -1;
        power_index += 2;
    }

    return result;
}
