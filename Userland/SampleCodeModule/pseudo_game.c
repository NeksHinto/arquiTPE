#include <video_module.h>
#include <stdio.h>
#include <stdlib.h>
#include <sound_module.h>
#include <time_module.h>
#include <pseudo_game.h>

static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;

static int score;
static int current_direction;
static int aux_time_played;
static int start_time;
static int aux_time;
static int real_time_played;

static const Color white = {225,225,225};
static const Color black = {0,0,0};
static const Color green = {4, 242, 32};
static const Color red = {255, 0, 0};
static const Color yellow = {255, 255, 0};
static const Color violet = {120, 40, 140};


/** Static prototypes */
static void draw_player();
static Game start_game();
static void draw_borders_arc(Color color);
static void draw_entity(Entity entity);
static void update_ball();
static void update_player();
static int there_is_impact();

static GameADT game;

static void draw_borders_arc(Color color) {
    write_block(0, 0, SCREEN_WIDTH, BORDER_WIDTH, color); // Top screen
    write_block(0, BORDER_Y_COORD, SCREEN_WIDTH, BORDER_WIDTH, color); // Top Game field
    write_block(0, 0, BORDER_WIDTH, SCREEN_HEIGHT, color); // Left
    write_block(SCREEN_WIDTH - BORDER_WIDTH, 0, BORDER_WIDTH, SCREEN_HEIGHT, color); // Right
}

static Game start_game(){
    Game game_started = (Game){
                                .player = { {.x = SCREEN_WIDTH/2 - 30, .y = SCREEN_HEIGHT - 10},{.x = 0, .y = 0}, 20, 60, TRUE, green},
                                .ball = { {.x= SCREEN_WIDTH/2 - 5, .y = SCREEN_HEIGHT - 20},{.x = 0, .y = -20}, 10, 10, TRUE, yellow},
                                .blocks = {
                                            { {.x = SCREEN_WIDTH/8 - 30, .y = SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = SCREEN_WIDTH/8 - 30, .y = 2 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, violet },
                                            { {.x = SCREEN_WIDTH/8 - 30, .y = 3 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = 2 * SCREEN_WIDTH/8 - 30, .y = SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, violet },
                                            { {.x = 2 * SCREEN_WIDTH/8 - 30, .y = 2 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = 2 * SCREEN_WIDTH/8 - 30, .y = 3 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, violet },
                                            { {.x = 3 * SCREEN_WIDTH/8 - 30, .y = SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = 3 * SCREEN_WIDTH/8 - 30, .y = 2 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, violet},
                                            { {.x = 3 * SCREEN_WIDTH/8 - 30, .y = 3 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = 5 * SCREEN_WIDTH/8 - 30, .y = SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = 5 * SCREEN_WIDTH/8 - 30, .y = 2 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, violet },
                                            { {.x = 5 * SCREEN_WIDTH/8 - 30, .y = 3 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = 6 * SCREEN_WIDTH/8 - 30, .y = SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, violet },
                                            { {.x = 6 * SCREEN_WIDTH/8 - 30, .y = 2 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = 6 * SCREEN_WIDTH/8 - 30, .y = 3 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, violet },
                                            { {.x = 7 * SCREEN_WIDTH/8 - 30, .y = SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                            { {.x = 7 * SCREEN_WIDTH/8 - 30, .y = 2 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, violet },
                                            { {.x = 7 * SCREEN_WIDTH/8 - 30, .y = 3 * SCREEN_HEIGHT/6 - 15 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                                          },
                                .game_over = FALSE,
                                .remaining_blocks = MAX_BLOCKS,
                                .score = 0,
    };
    return game_started;
}

static void draw_game(){
    fill_screen(black);
    draw_borders_arc(white);
    draw_player();
    draw_entity(game->ball);
    for( int i = 0; i < MAX_BLOCKS; i++ ){
        draw_entity(game->blocks[i]);
    }
}

static void draw_gameBoard(){
    char time[9] = {'0','0', '.', '0', '0', '.', '0', '0', '\0'};
    char score[8] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
    char aux[8];
    int i, j, length = 0;

    real_time_played = get_seconds() - start_time;
    write_sized_string("TIME: ", 15, 15, white, black, 2, 15);
    itoa(real_time_played / 3600, 10, time + 0 );
    if( time[1] == 0 ){
        time[1] = time[0];
        time[0] = '0';
    }
    else{
        time[2] = '.';
    }
    itoa((real_time_played / 60) % 60, 10, time + 3 );
    if( time[4] == 0 ){
        time[4] = time[3];
        time[3] = '0';
    }
    else{
        time[5] = '.';
    }
    itoa(real_time_played % 60, 10, time + 6);
    if( time[7] == 0 ){
        time[7] = time[6];
        time[6] = '0';
    }
    write_sized_string(time, 6 * 20, 15, white, black, 2, 15);
    write_sized_string("POINTS: ", SCREEN_WIDTH - 285, 15, white, black, 2, 15);
    itoa(game->score, 10, aux);
    length = strlen(aux);
    for(i = 7 - length, j = 0; game->score != 0 && i < 8; i++, j++)
        score[i] = aux[j];
    write_sized_string(score, SCREEN_WIDTH - 135, 15, white, black, 2, 15);
}

static void draw_entity( Entity entity ){
    write_block(entity.position.x,entity.position.y, entity.width, entity.height, entity.color);
}

static void delete_entity( Entity entity ){
    write_block(entity.position.x,entity.position.y, entity.width, entity.height, black);
}

static void update_ball(){
    delete_entity(game->ball);
    game->ball.position = (Position){
                                     .x = game->ball.position.x + game->ball.speed.x,
                                     .y = game->ball.position.y + game->ball.speed.y };
    draw_entity(game->ball);
}

static void update_player(int n){
    delete_entity(game->player);
    game->player.position = (Position){
                                        .x = game->player.position.x + n,
                                        .y = game->player.position.y };
    draw_entity(game->player);
}

static void draw_player() {
    write_block(game->player.position.x, game->player.position.y, game->player.width, game->player.height, game->player.color);
}

static int there_is_impact(){
    for( int i = 0; i < MAX_BLOCKS; i++ ){
        if( game->ball.position.x >= (*(game->blocks + i)).position.x &&
            game->ball.position.x < (*(game->blocks + i)).position.x + (*(game->blocks + i)).height &&
            game->ball.position.y >= (*(game->blocks + i)).position.y &&
            game->ball.position.y < (*(game->blocks + i)).position.y + (*(game->blocks + i)).width )
            return TRUE;
    }
    return FALSE;
}

int get_seconds() {
    char hours[3];
    itoa(system_hours(), 16, hours);
    char minutes[3];
    itoa(system_minutes(), 16, minutes);
    char seconds[3];
    itoa(system_seconds(), 16, seconds);

    return (atoi(hours) * 3600) + (atoi(minutes) * 60) + atoi(seconds);
}

Speed hits_player( Entity ball, Entity player ){
    int x1,y1,x2,y2;
    int PLAYER_LEFT_SIDE = player.position.x + (player.width / 6);
    int PLAYER_RIGHT_SIDE = player.position.x + player.width - (player.width / 6);
    Speed bounce_speed = { .x = 0, .y = 0 };

    // checks left side
    for( x1 = ball.position.x; x1 < ball.position.x + ball.width; x1++ ){
        for( y1 = ball.position.y; y1 < ball.position.y + ball.height; y1++ ){
            for( x2 = player.position.x; x2  < PLAYER_LEFT_SIDE; x2++ ){
                for( y2 = player.position.y; y2 < player.position.y + player.height; y2++ ){
                    if( x1 == x2 && y1 == y2 ){
                        bounce_speed.y = ball.speed.y * -1;
                        bounce_speed.x = bounce_speed.y;
                        return bounce_speed;
                    }
                }
            }
        }
    }
    // checks right side
    for( x1 = ball.position.x; x1 < ball.position.x + ball.width; x1++ ){
        for( y1 = ball.position.y; y1 < ball.position.y + ball.height; y1++ ){
            for( x2 = PLAYER_RIGHT_SIDE; x2  < player.position.x + player.width; x2++ ){
                for( y2 = player.position.y; y2 < player.position.y + player.height; y2++ ){
                    if( x1 == x2 && y1 == y2 ){
                        bounce_speed.y = ball.speed.y * -1;
                        bounce_speed.x = bounce_speed.y * -1;
                        return bounce_speed;
                    }
                }
            }
        }
    }
    // checks center
    for( x1 = ball.position.x; x1 < ball.position.x + ball.width; x1++ ){
        for( y1 = ball.position.y; y1 < ball.position.y + ball.height; y1++ ){
            for( x2 = PLAYER_LEFT_SIDE -1; x2  < PLAYER_RIGHT_SIDE; x2++ ){
                for( y2 = player.position.y; y2 < player.position.y + player.height; y2++ ){
                    if( x1 == x2 && y1 == y2 ){
                        bounce_speed.y = ball.speed.y * -1;
                        bounce_speed.x = 0;
                        return bounce_speed;
                    }
                }
            }
        }
    }
    return bounce_speed;
}


int check_impact( Entity ball, Entity blocks[]){
 int i, x1, x2, y1, y2;

    for( i = 0; i < MAX_BLOCKS; i++ ){
        if( blocks[i].visible ){
            for( x1 = ball.position.x; x1 < ball.position.x + ball.width; x1++ ){
                for( y1 = ball.position.y; y1 < ball.position.y + ball.height; y1++ ){
                    if( x1 >= blocks[i].position.x && x1 < blocks[i].position.x + blocks[i].width &&
                        y1 >= blocks[i].position.y && y1 < blocks[i].position.y + blocks[i].height ){
                        delete_entity(blocks[i]);
                        blocks[i].visible = FALSE;
                        game->score += 10;
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}


/*********** Aracnoid *************/

Game pseudo_game(){
    int ticks, time_counter, is_moving, paused_game;
    char c;
    paused_game = FALSE;
    is_moving = FALSE;
    SCREEN_WIDTH = get_screen_width();
    SCREEN_HEIGHT = get_screen_height();
    Game aux;
    Speed direction = {.x = 0, .y = 0};


    //bool leave = false;
    //int currentGameTick = 0, previusGameTick =0;

//    do{
//        currentGameTick = getTicks();
//
//        ParseInput();
//
//        if((currentGameTick % 1) == 0 && currentGameTick != previusGameTick){
//            previusGameTick = currentGameTick;
//
//            runGame();
//
//        }
//
//    }while (!leave);

    aux = start_game();
    game = &aux;
    score = 0;
    start_game();
    draw_game();

    time_counter = ticks_elapsed();
    start_time = get_seconds();
    while((c = getchar()) != 'x' && c != 'X' && c != 'p' && c != 'P'){
        if( c == 'd' && game->player.position.x <= SCREEN_WIDTH - 15 - game->player.width ){
            game->player.speed.x = 30;
            update_player(30);
            is_moving = TRUE;
        }
        else if( c == 'a' && game->player.position.x >= 20){
            game->player.speed.x = -30;
            update_player(-30);
            is_moving = TRUE;
        }

        if( ticks_elapsed() - time_counter >= 1 ){
            if( game->ball.position.y + game->ball.height > SCREEN_HEIGHT - 30){
                direction = hits_player(game->ball, game->player);
                if(direction.x != 0 || direction.y != 0){
                    game->ball.speed.y = direction.y;
                    game->ball.speed.x = direction.x;
                }
            }
            if( game->ball.position.x <= 27 || game->ball.position.x >= SCREEN_WIDTH - 27 ){
                game->ball.speed.x =- game->ball.speed.x;
            }
            if( game->ball.position.y <= BORDER_Y_COORD + 18 ){
                game->ball.speed.y = -game->ball.speed.y;

            }
            if( game->ball.position.y > SCREEN_HEIGHT ){
                game->game_over = TRUE;
            }
            if( !is_moving ){
                game->ball.speed.x == 0;
            }
            update_ball();
            draw_player();
            draw_borders_arc(white);
            draw_gameBoard();
            time_counter = ticks_elapsed();
            is_moving = FALSE;
        }

        while(game->game_over){
            write_sized_string("GAME OVER", 40, 500, white, black, 10, 100);
            write_sized_string("PRESS [SPACE] TO PLAY AGAIN OR [X] TO EXIT", 150, 650, white, black, 2, 15);
            if((c=getchar())==' '){
                game->game_over=FALSE;
                aux = start_game();
                game = &aux;
                score = 0;
                start_game();
                draw_game();
                start_time = get_seconds();
                draw_gameBoard();
            }
        }

        if( game->ball.position.y <= 4 * SCREEN_HEIGHT / 6 && check_impact(game->ball, game->blocks) ){
            game->ball.speed.y = -game->ball.speed.y;
        }
    }

    // if( c == 'p' || c == 'P' ){
    //     return aux;
    // }
    // game->game_over = TRUE;
    // return aux;
}
