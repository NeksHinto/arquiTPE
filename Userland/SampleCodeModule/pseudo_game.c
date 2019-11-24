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
static int increase_timer;
static int aux_time;
static int real_time_played;

static const Color white = {225,225,225};
static const Color black = {0,0,0};
static const Color green = {4, 242, 32};
static const Color red = {255, 0, 0};


/** Static prototypes */
static void draw_player();
static void start_game();
static void draw_borders_arc(Color color);
static void draw_entity(Entity entity);
static void update_ball();
static void update_player();
static int there_is_impact();
static void game_refresh();

GameADT game;

static void draw_borders_arc(Color color) {
    write_block(0, 0, SCREEN_WIDTH, 10, color);
    write_block(0, SCREEN_HEIGHT-10, SCREEN_WIDTH, 10, color);
    write_block(0, 0, 10, SCREEN_HEIGHT, color);
    write_block(SCREEN_WIDTH-10, 0, 10, SCREEN_HEIGHT, color);
}

static void start_game(){

    Game aux;
    aux = (Game){
            .player = { {.x = 540, .y = 0},{.x = 0, .y = 0}, 10, 20, green},
            .ball = { {.x=5, .y = 1},{.x = 0, .y = 0}, 1, 1, white},
            .blocks = {
                    { {.x = 0, .y = 20 }, {.x = 0, .y = 0}, 5, 5, red },
                    { {.x = 5, .y = 20 }, {.x = 0, .y = 0}, 5, 5, red }
            },
            .game_over = FALSE
    };
    game = &aux;
    SCREEN_WIDTH = get_screen_width();
    SCREEN_HEIGHT = get_screen_height();
    score = 0;
    game->blocks_q = 0;
    fill_screen(black);
    draw_borders_arc(white);
    draw_player();
}

static void draw_entity( Entity entity ){
    write_block(entity.position.x,entity.position.y, entity.width, entity.height, entity.color);
}

static void update_ball(){
  game->ball.position = (Position){.x = game->ball.position.x + game->ball.speed.x,
                         .y = game->ball.position.y + game->ball.speed.y};
}

static void update_player(){
  game->player.position = (Position){ .x = game->player.position.x + game->player.speed.x,
                            .y = game->player.position.y + game->player.speed.y};
}

static void draw_player(Color color) {
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
  update_player();
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

Game* pseudo_game(){
    start_game();
    while(1);
}
