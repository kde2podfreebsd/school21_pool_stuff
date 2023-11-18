// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define FIELD_SIZE_X 80
#define FIELD_SIZE_Y 25
#define RACKET_SIZE 3
#define BALL_SIZE 1
#define WIN_CONDITION 21
#define ANGLE 29.4
#define INITIAL_SPEED 1

void print_start_screen();
void play_pong();
void print_win_screen(int score_p1, int score_p2);

double rad(double degrees);

void update_screen(int score_p1, int score_p2, int ball_x1, int ball_y1, int racket_p1_y, int racket_p2_y);
void print_pong();

int move_racket(int player, int racket_y);

int main() {
    initscr();
    noecho();
    keypad(stdscr, 1);
    curs_set(0);
    nodelay(stdscr, 1);
    print_start_screen();
    play_pong();
    endwin();
    clear();
    refresh();
    return 0;
}

void print_start_screen() {
    char ch;
    clear();
    update_screen(21, 0, FIELD_SIZE_X / 2 + 1, FIELD_SIZE_Y / 2 + 1, FIELD_SIZE_Y / 2 - 1,
                  FIELD_SIZE_Y / 2 - 1);
    printw("Press Enter to start the game: ");
    refresh();
    scanf("%c", &ch);
}

void play_pong() {
    int score_p1 = 0, score_p2 = 0;
    int speed = INITIAL_SPEED;
    while (score_p1 < WIN_CONDITION && score_p2 < WIN_CONDITION) {
        int racket_p1_y, racket_p2_y;
        racket_p1_y = racket_p2_y = FIELD_SIZE_Y / 2 - 1;
        double ball_x1 = FIELD_SIZE_X / 2. + 1, ball_y1 = FIELD_SIZE_Y / 2.;
        int ball_dir_y = 1, ball_dir_x = 1;
        while (ball_x1 >= 3 && ball_x1 <= FIELD_SIZE_X - 2) {
            usleep(100000);
            int action_p1 = getch();
            double ball_x2 = ball_x1 + ball_dir_x * speed * cos(rad(ANGLE));
            double ball_y2 = ball_y1 + ball_dir_y * speed * sin(rad(ANGLE));
            if (ball_y2 < 1) {
                ball_y2 = 2 - ball_y2;
                ball_dir_y = -ball_dir_y;
            }
            if (ball_y2 > FIELD_SIZE_Y) {
                ball_y2 = FIELD_SIZE_Y * 2 - ball_y2;
                ball_dir_y = -ball_dir_y;
            }
            double y_l_cross = ball_dir_y * tan(rad(ANGLE)) * (3 - ball_x1) + ball_y1;
            double y_r_cross = ball_dir_y * tan(rad(ANGLE)) * (FIELD_SIZE_X - 2 - ball_x1) + ball_y1;
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
            update_screen(score_p1, score_p2, ball_x1, ball_y1, racket_p1_y, racket_p2_y);
            if ((action_p1 == 'a' || action_p1 == 'A') && racket_p1_y >= 2) {
                racket_p1_y -= 1;
            } else if ((action_p1 == 'z' || action_p1 == 'Z') && racket_p1_y <= FIELD_SIZE_Y - RACKET_SIZE) {
                racket_p1_y += 1;
            } else if ((action_p1 == 'k' || action_p1 == 'K') && racket_p2_y >= 2) {
                racket_p2_y -= 1;
            } else if ((action_p1 == 'm' || action_p1 == 'M') && racket_p2_y <= FIELD_SIZE_Y - RACKET_SIZE) {
                racket_p2_y += 1;
            }
        }
        score_p1 = ball_x1 > FIELD_SIZE_X - 2 ? score_p1 + 1 : score_p1;
        score_p2 = ball_x1 < 3 ? score_p2 + 1 : score_p2;
    }
    print_win_screen(score_p1, score_p2);
}

void print_pong() {
    for (int i = 0; i <= FIELD_SIZE_X + 1; i++) printw("-");
    printw("\n");
    printw("|               ##########     ########     #          #     ########            |\n");
    printw("|              #          #   #        #    # #        #    #        #           |\n");
    printw("|              #          #   #        #    #  #       #    #                    |\n");
    printw("|              #          #   #        #    #   #      #    #                    |\n");
    printw("|              ###########    #        #    #    #     #    #                    |\n");
    printw("|              #              #        #    #     #    #    #   #####            |\n");
    printw("|              #              #        #    #      #   #    #        #           |\n");
    printw("|              #              #        #    #       #  #    #        #           |\n");
    printw("|              #              #        #    #        # #    #        #           |\n");
    printw("|              #               ########     #          #     ########            |\n");
    refresh();
}

void update_screen(int score_p1, int score_p2, int ball_x1, int ball_y1, int racket_p1_y, int racket_p2_y) {
    clear();
    print_pong();

    printw("| Player1                                                                Player2 |\n");
    printw("| UP - A, DOWN - Z, ' ' - skip        %2d : %-2d       UP - K, DOWN - M, ' ' - skip |\n",
           score_p1, score_p2);
    for (int x = 0; x <= FIELD_SIZE_X + 1; x++) printw("-");
    printw("\n");

    for (int y = 1; y <= FIELD_SIZE_Y; y++) {
        printw("|");
        for (int x = 1; x <= FIELD_SIZE_X; x++) {
            if (y >= racket_p1_y && y <= racket_p1_y + (RACKET_SIZE - 1) && x == 3)
                printw("|");
            else if (y >= racket_p2_y && y <= racket_p2_y + (RACKET_SIZE - 1) && x == FIELD_SIZE_X - 2)
                printw("|");
            else if (y == ball_y1 && x == ball_x1)
                printw("*");
            else if (x == FIELD_SIZE_X / 2 + 1)
                printw("|");
            else
                printw(" ");
        }
        printw("|\n");
    }

    for (int i = 0; i <= FIELD_SIZE_X + 1; i++) printw("-");
    printw("\n");
    refresh();
}

void print_win_screen(int score_p1, int score_p2) {
    update_screen(score_p1, score_p2, FIELD_SIZE_X / 2 + 1, FIELD_SIZE_Y / 2 + 1, FIELD_SIZE_Y / 2 - 1,
                  FIELD_SIZE_Y / 2 - 1);
    if (score_p1 == WIN_CONDITION)
        printw("Player 1 WON!!! Congratulations!\n");
    else
        printw("Player 2 WON!!! Congratulations!\n");
    refresh();
    sleep(10);
}

double rad(double degrees) { return degrees * M_PI / 180.0; }
