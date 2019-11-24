//
//#include <snake.h>
//#include <video_module.h>
//#include <stdio.h>
//#include <sound_module.h>
//#include <time_module.h>
//
//typedef struct {
//    int x;
//    int y;
//} pos_t;
//
//typedef struct {
//    int length;
//    pos_t body[100];
//} snake_t;
//
//static int SCREEN_WIDTH;
//static int SCREEN_HEIGHT;
//
//#define UP 0
//#define DOWN 1
//#define LEFT 2
//#define RIGTH 3
//
//#define NULL 0
//#define TRUE 1
//#define FALSE 0
//
//static snake_t snake;
//static int score;
//static int current_direction;
//static int aux_time_played;
//static int increaser_timer;
//
//static int aux_time;
//static int real_time_played;
//
//
//
//static const Color white = {225,225,225};
//static const Color black = {0,0,0};
//static const Color green = {4, 242, 32};
//static const Color red = {255, 0, 0};
//
//static void init_game(void);
//static int move_snake();
//static void draw_skeleton(void);
//
//
//static void init_snake(void){
//  SCREEN_WIDTH = get_screen_width();
//  SCREEN_HEIGHT = get_screen_height();
//
//  score = 0;
//
//  (snake.body)[0].x = (snake.body)[1].x = (snake.body)[2].x = (snake.body)[3].x = (SCREEN_WIDTH/2) - 5;
//  snake.length = 4;
//
//  int y = ((3 * SCREEN_HEIGHT)/4);
//
//  (snake.body)[0].y = y;
//  (snake.body)[1].y = y + 15;
//  (snake.body)[2].y = y + 30;
//  (snake.body)[3].y = y + 45;
//  draw_skeleton();
//}
//
//static void draw_skeleton(void) {
//    fill_screen(black);
//    draw_borders(white);
//    draw_snake(green);
//}
//
//void snake_game() {
//    int playing = TRUE;
//    while (playing) {
//        init_snake();
//        char c;
//        current_direction = UP;
//        int direction = current_direction;
//        int old_ticks = 0;
//        char welcome_message[] = "Press [SPACE] to start! [X] to exit!";
//        print_message(welcome_message, 37, white);
//        while((c = getchar()) != ' ' && c != 'x') {}
//        if (c == 'x') return;
//        print_message(welcome_message, 37, black);
//        int snake_alive = 1;
//        double snake_speed = 1.5;
//        aux_time = increaser_timer = get_time();
//        real_time_played = 0;
//        while((c = getchar()) != 'x' && snake_alive) { // Hasta que no toque 'X' no va a salir del juego.
//            int ticks = ticks_elapsed();
//            switch(c) {
//                case 'w':
//                    direction = UP;
//                    break;
//                case 'a':
//                    direction = LEFT;
//                    break;
//                case 's':
//                    direction = DOWN;
//                    break;
//                case 'd':
//                    direction = RIGTH;
//                    break;
//                default:
//                    break;
//            }
//            if(c == 'p') {
//                int aux_increaser_time = get_time() - increaser_timer;
//                char pause_message[] = "PAUSE! [X] to exit. [P] to resume!";
//                print_message(pause_message, 35, white);
//                while((c = getchar()) != 'p' && c != 'x') {}
//                print_message(pause_message, 35, black);
//                increaser_timer = get_time() - aux_increaser_time;
//                aux_time = get_time();
//                if (c == 'x') return;
//            }
//            if (fifteen_seconds_function(get_time())) {
//                snake.length++;
//                snake_speed -= 0.25;
//                beep(1);
//                score++;
//            }
//            if (old_ticks + snake_speed < ticks) {
//                snake_alive = move_snake(direction);
//                old_ticks = ticks;
//            }
//            if (get_time() != aux_time) {
//                real_time_played += (get_time() - aux_time);
//                aux_time = get_time();
//            }
//        }
//        playing = FALSE;
//        if (!snake_alive) {
//            char game_over_message[] = "Game Over! [X] to exit. [R] to play again!";
//            print_message(game_over_message, 43, white);
//            print_time_played(white);
//            while((c = getchar()) != 'r' && c != 'x') {}
//            print_message(game_over_message, 43, black);
//            if (c == 'r') playing = TRUE;
//        }
//    }
//}
//
//int move_snake(int direction) {
//    current_direction = valid_direction(direction);
//    int x, y;
//    switch (current_direction) {
//        case UP:
//            x = 0;
//            y = -15;
//            break;
//        case DOWN:
//            x = 0;
//            y = 15;
//            break;
//        case RIGTH:
//            x = 15;
//            y = 0;
//            break;
//        case LEFT:
//            x = -15;
//            y = 0;
//            break;
//        default:
//            break;
//    }
//
//    if (!valid_position(x, y)) {
//        draw_snake(red);
//        beep(4);
//        return 0;
//    }
//    draw_block((snake.body)[snake.length - 1], black);
//    for(int i = snake.length - 1;  i > 0 ; i--) {
//        (snake.body)[i].x = (snake.body)[i-1].x;
//        (snake.body)[i].y = (snake.body)[i-1].y;
//    }
//
//    (snake.body)[0].x += x;
//    (snake.body)[0].y += y;
//    handle_borders();
//    draw_time(white);
//    draw_borders(white);
//    draw_snake(green);
//    return 1;
//}
//
//void draw_snake(Color color) {
//    int count = 0;
//    for(int i = 0 ;  i < snake.length ; i++) {
//        write_block((snake.body)[i].x, (snake.body)[i].y, 10, 10, color);
//    }
//}
//int valid_direction(int dir) {
//    if (dir == current_direction) return current_direction;
//    if ((dir ==  UP && current_direction == DOWN) || (dir == DOWN && current_direction == UP)) return current_direction;
//    if ((dir ==  LEFT && current_direction == RIGTH) || (dir == RIGTH && current_direction == LEFT)) return current_direction;
//    return dir;
//}
//
//void print_message(char message[], int length, Color color) {
//    int spacing = 10;
//    int size = 2;
//    int x = 100;
//    int y = SCREEN_HEIGHT - 100;
//    for(int i = 0 ; i < length ; i++) {
//        write_sized_char( message[i],  x + i*spacing*size, y, color, black, size);
//    }
//}
//
//void print_time_played(Color color) {
//    int pos_x = 100;
//    int pos_y_time = 200;
//    int pos_y_score = 240;
//    int SIZE = 2;
//    int spacing = 10;
//    char time_message[] = " Seconds Played:    ";
//    char score_message[] = " Score:   ";
//    int score_message_length = 11;
//    int time_message_length = 21;
//    char time[3];
//    itoa(real_time_played, 10, time);
//    char aux_score[2];
//    itoa(score, 10, aux_score);
//    score_message[9] = aux_score[0];
//    score_message[10] = aux_score[1];
//    time_message[17] = time[0];
//    time_message[18] = time[1];
//    time_message[19] = time[2];
//    int x_aux = pos_x;
//    for(int i = 0, x_aux = pos_x; i < time_message_length ; i++, x_aux += spacing * SIZE) {
//        write_sized_char( time_message[i],  x_aux, pos_y_time, color, black, SIZE);
//    }
//    for(int i = 0, x_aux = pos_x; i < score_message_length ; i++, x_aux += spacing * SIZE) {
//            write_sized_char( score_message[i],  x_aux, pos_y_score, color, black, SIZE);
//        }
//}
//
//void draw_time(Color color) {
//    int cents = real_time_played / 10;
//
//    int time_left = cents /10;
//    int time_middle = cents %10;
//    int time_right = real_time_played %10;
//
//    int TIME_SIZE = 10;
//
//    write_sized_char( time_left + '0',  20, 10, color, black, TIME_SIZE);
//    write_sized_char( time_middle + '0',  100, 10, color, black, TIME_SIZE);
//    write_sized_char( time_right + '0',  180, 10, color, black, TIME_SIZE);
//}
//
//void draw_borders(Color color) {
//    write_block(0, 0, SCREEN_WIDTH, 10, color);
//    write_block(0, SCREEN_HEIGHT-10, SCREEN_WIDTH, 10, color);
//    write_block(0, 0, 10, SCREEN_HEIGHT, color);
//    write_block(SCREEN_WIDTH-10, 0, 10, SCREEN_HEIGHT, color);
//}
//
//void draw_block(pos_t block, Color color) {
//    write_block(block.x, block.y, 10, 10, color);
//}
//
//int valid_position(int x, int y) {
//    int new_x = (snake.body)[0].x + x;
//    int new_y = (snake.body)[0].y + y;
//
//    for(int i = 1 ; i < snake.length ; i++) {
//        pos_t body = (snake.body)[i];
//        int aux_x = body.x - new_x;
//        int aux_y = body.y - new_y;
//        if ((aux_x < 15 && aux_x > -15) && (aux_y < 15 && aux_y > -15)) {
//            return 0;
//        }
//    }
//    return 1;
//}
//
//void handle_borders() {
//    if ((snake.body)[0].x > SCREEN_WIDTH - 20) {
//        (snake.body)[0].x = 12;
//    }
//    if ((snake.body)[0].x < 10) {
//        (snake.body)[0].x = SCREEN_WIDTH - 22;
//    }
//    if ((snake.body)[0].y < 10) {
//        (snake.body)[0].y = SCREEN_HEIGHT - 22;
//    }
//    if ((snake.body)[0].y > SCREEN_HEIGHT - 20) {
//        (snake.body)[0].y = 12;
//    }
//}
//
//int get_time() {
//    char hours[3];
//    itoa(system_hours(), 16, hours);
//    char minutes[3];
//    itoa(system_minutes(), 16, minutes);
//    char seconds[3];
//    itoa(system_seconds(), 16, seconds);
//
//    return (atoi(hours) * 3600) + (atoi(minutes) * 60) + atoi(seconds);
//}
//
//int fifteen_seconds_function(int time) {
//    if (increaser_timer <= time - 15) {
//        increaser_timer = time;
//        return 1;
//    }
//    return 0;
//}