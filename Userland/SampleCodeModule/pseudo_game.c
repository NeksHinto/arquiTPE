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

static void game_refresh(){
    if( there_is_impact() ){
        game->game_over = TRUE;
        return;
    }

    draw_entity( game->ball );
    draw_entity( game->player );

    update_ball();
    update_player(1);
}
//
//Game* pseudo_game( Game* saved_game ){
//   char c;
//    if( saved_game == NULL){
//        start_game();
//    }
//    else{
//        game = saved_game;
//    }
//
//    while( !game->game_over ){
//        game_refresh();
//    }
//
//    return game;
//}

int get_seconds() {
    char hours[3];
    itoa(system_hours(), 16, hours);
    char minutes[3];
    itoa(system_minutes(), 16, minutes);
    char seconds[3];
    itoa(system_seconds(), 16, seconds);

    return (atoi(hours) * 3600) + (atoi(minutes) * 60) + atoi(seconds);
}

Game* pseudo_game(){
    int ticks, time_counter;
    char c;
    SCREEN_WIDTH = get_screen_width();
    SCREEN_HEIGHT = get_screen_height();
    Game aux;
    aux = (Game){
            .player = { {.x = SCREEN_WIDTH/2 - 30, .y = SCREEN_HEIGHT - 10},{.x = 0, .y = 0}, 20, 60, green},
            .ball = { {.x= SCREEN_WIDTH/2 - 5, .y = SCREEN_HEIGHT - 20},{.x = 0, .y = -20}, 10, 10, yellow},
            .blocks = {
                    { {.x = 30, .y = 10 }, {.x = 0, .y = 0}, 30, 60, red },
                    { {.x = SCREEN_WIDTH - 90, .y = 10 }, {.x = 0, .y = 0}, 30, 60, red }
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
    time_counter = get_seconds();
    while((c = getchar()) != 'x' && c != 'X'){
        if( c == 'd' && game->player.position.x <= SCREEN_WIDTH - 15 - game->player.width ){
            update_player(10);
        }
        else if( c == 'a' && game->player.position.x >= 20){
            update_player(-10);
        }

        if( get_seconds() - time_counter >= 1 ){
            if( game->ball.position.y <= 10 ){
                game->ball.speed.y = 25;
            }
            update_ball();
            time_counter = get_seconds();
        }


    }
    return NULL;
}
