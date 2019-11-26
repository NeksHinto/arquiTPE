#include <video_module.h>
#include <stdio.h>
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


/** Static prototypes */
static void draw_player();
static void start_game();
static void draw_borders_arc(Color color);
static void draw_entity(Entity entity);
static void update_ball();
static void update_player();
static int there_is_impact();
static void game_refresh();

static GameADT game;

static void draw_borders_arc(Color color) {
    write_block(0, 0, SCREEN_WIDTH, 10, color); // Top
    //write_block(0, SCREEN_HEIGHT-10, SCREEN_WIDTH, 10, color); // Bottom
    write_block(0, 0, 10, SCREEN_HEIGHT, color); // Left
    write_block(SCREEN_WIDTH-10, 0, 10, SCREEN_HEIGHT, color); // Right
}

static void start_game(){


    for( int i = 0; i < MAX_BLOCKS; i++ ){
        draw_entity(game->blocks[i]);
    }
}

static void draw_entity( Entity entity ){
    write_block(entity.position.x,entity.position.y, entity.width, entity.height, entity.color);
}

static void delete_entity( Entity entity ){
    write_block(entity.position.x,entity.position.y, entity.width, entity.height, black);
}

static void update_ball(){
    delete_entity(game->ball);
    game->ball.position = (Position){.x = game->ball.position.x + game->ball.speed.x,
            .y = game->ball.position.y + game->ball.speed.y};
    draw_entity(game->ball);
}

static void update_player( int n){
    delete_entity(game->player);
    game->player.position = (Position){ .x = game->player.position.x + n,
            .y = game->player.position.y};
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

int hits_player( Entity ball, Entity player ){
    int x1,y1,x2,y2;
    for( x1 = game->ball.position.x; x1 < game->ball.position.x + game->ball.width; x1++ ){
        for( y1 = game->ball.position.y; y1 < game->ball.position.y + game->ball.height; y1++ ){
            for( x2 = game->player.position.x; x2  < game->player.position.x + game->player.width; x2++ ){
                for( y2 = game->player.position.y; y2 < game->player.position.y + game->player.height; y2++ ){
                    if( x1 == x2 && y1 == y2 ){
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

int check_impact( Entity ball, Entity blocks[]){
    int i, x1, x2, y1, y2;

    for( i = 0; i < MAX_BLOCKS; i++ ){
        if( blocks[i].visible ){
            for( x1 = ball.position.x; x1 < ball.position.x + ball.width; x1++ ){
                for( y1 = ball.position.y; y1 < ball.position.y + ball.height; y1++ ){
                    for( x2 = blocks[i].position.x; x2 < blocks[i].position.x + blocks[i].width; x2++ ){
                        for( y2 = blocks[i].position.y; y2 < blocks[i].position.y + blocks[i].height; y2++ ){
                            if( x1 == x2 && y1 == y2 ){
                                delete_entity(blocks[i]);
                                blocks[i].visible = FALSE;
                                return TRUE;
                            }
                        }
                    }
                }
            }
        }
    }

    return FALSE;
}

Game pseudo_game(){
    int ticks, time_counter, is_moving;
    char c;
    is_moving = FALSE;
    SCREEN_WIDTH = get_screen_width();
    SCREEN_HEIGHT = get_screen_height();
    Game aux;
    aux = (Game){
            .player = { {.x = SCREEN_WIDTH/2 - 30, .y = SCREEN_HEIGHT - 10},{.x = 0, .y = 0}, 20, 60, TRUE, green},
            .ball = { {.x= SCREEN_WIDTH/2 - 5, .y = SCREEN_HEIGHT - 20},{.x = 0, .y = -10}, 10, 10, TRUE, yellow},
            .blocks = {
                    { {.x = SCREEN_WIDTH/2 - 20, .y = SCREEN_HEIGHT/2 - 20 }, {.x = 0, .y = 0}, 30, 60, TRUE, red },
                    { {.x = SCREEN_WIDTH - 200, .y = SCREEN_HEIGHT - 300 }, {.x = 0, .y = 0}, 30, 60, TRUE, red }
            },
            .game_over = FALSE
    };
    game = &aux;
    score = 0;
    game->remaining_blocks = 0;


    fill_screen(black);
    draw_borders_arc(white);
    draw_player();
    draw_entity(game->ball);
    start_game();
    time_counter = ticks_elapsed();
    while((c = getchar()) != 'x' && c != 'X' && c != 'p' && c != 'P' && !game->game_over ){
        if( c == 'd' && game->player.position.x <= SCREEN_WIDTH - 15 - game->player.width ){
            game->player.speed.x = 10;
            update_player(10);
            is_moving = TRUE;
        }
        else if( c == 'a' && game->player.position.x >= 20){
            game->player.speed.x = -10;
            update_player(-10);
            is_moving = TRUE;
        }

        if( ticks_elapsed() - time_counter >= 1 ){
            if( hits_player(game->ball, game->player) ){
                if( is_moving ){
                    game->ball.speed.x = - game->player.speed.x;
                }
                game->ball.speed.y = -game->ball.speed.y;
            }
            if( game->ball.position.x <= 27 || game->ball.position.x >= SCREEN_WIDTH - 27 ){
                game->ball.speed.x = -game->ball.speed.x;
            }
            if( game->ball.position.y <= 27 ){
                game->ball.speed.y = -game->ball.speed.y;
            }
            if( game->ball.position.y > SCREEN_HEIGHT ){
                game->game_over = TRUE;
            }
            update_ball();
            time_counter = ticks_elapsed();
            is_moving = FALSE;
        }

        if( check_impact(game->ball, game->blocks) ){
            game->ball.speed.y = -game->ball.speed.y;
        }
    }
    return aux;
}
