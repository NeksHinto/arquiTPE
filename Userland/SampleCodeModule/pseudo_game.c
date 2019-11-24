#include <video_module.h>
#include <stdio.h>
#include <sound_module.h>
#include <time_module.h>
#include <pseudo_game.h>

#define FALSE 0
#define MAX_BLOCKS 2
#define WHITE 1
#define BROWN 2
#define ORANGE 3
#define TRUE 1

static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;

static int score;
static int current_direction;
static int aux_time_played;
static int increaser_timer;
static int aux_time;
static int real_time_played;

static const Color white = {225,225,225};
static const Color black = {0,0,0};
static const Color green = {4, 242, 32};
static const Color red = {255, 0, 0};

typedef struct {
    int x,y;
} Position;

typedef struct {
    int x,y;
} Speed;

typedef struct {
    Position position;
    Speed speed;
    int height,width;
    Color color;
} Entity;

typedef struct {
    Entity blocks[MAX_BLOCKS];
    Entity ball;
    Entity player;
    int game_over;
    int blocks_q;
} Game;


static Game* game;

void draw_borders(Color color) {
    write_block(0, 0, SCREEN_WIDTH, 10, color);
    write_block(0, SCREEN_HEIGHT-10, SCREEN_WIDTH, 10, color);
    write_block(0, 0, 10, SCREEN_HEIGHT, color);
    write_block(SCREEN_WIDTH-10, 0, 10, SCREEN_HEIGHT, color);
}

void start_game(){
    *game = (Game){ .player = {{.x = 5, .y = 0},{.x = 1, .y = 0}, 1, 2, green},
             .ball = {{.x=5, .y = 1},{.x = 0, .y = 1}, 1, 1, white},
             .blocks = {{ {.x = 0, .y = 20 }, {.x = 0, .y = 0}, 5, 5, red },
                        { {.x = 5, .y = 20 }, {.x = 0, .y = 0}, 5, 5, red }
                       },
             .game_over = FALSE
            };
    SCREEN_WIDTH = get_screen_width();
    SCREEN_HEIGHT = get_screen_height(); 
    score = 0;
    game->blocks_q = 0;
    fill_screen(black);
    draw_borders(white);       
}

void draw_entity( Entity entity ){
    syscall(write_block_in_buffer(entity.position.x,entity.position.y, entity.width, entity.height, entity.color));
}

void update_ball(){
  game->ball.position = (Position){.x = game->ball.position.x + game->ball.speed.x,
                         .y = game->ball.position.y + game->ball.speed.y};
}

void update_player(){
  game->player.position = (Position){ .x = game->player.position.x + game->player.speed.x,
                            .y = game->player.position.y + game->player.speed.y};
}

int there_is_impact(){
  for( int i = 0; i < MAX_BLOCKS; i++ ){
    if( game->ball.position.x >= (*(game->blocks + i)).position.x &&
        game->ball.position.x < (*(game->blocks + i)).position.x + (*(game->blocks + i)).height &&
        game->ball.position.y >= (*(game->blocks + i)).position.y &&
        game->ball.position.y < (*(game->blocks + i)).position.y + (*(game->blocks + i)).width )
        return TRUE;
  }
  return FALSE;
}

void game_refresh(){
  if( there_is_impact() ){
    game->game_over = TRUE;
    return;
  }

  draw_entity( game->ball );
  draw_entity( game->player );

  update_ball();
  update_player();
}



void print_message(char message[], int length, Color color) {
    int spacing = 10;
    int size = 2;
    int x = 100;
    int y = SCREEN_HEIGHT - 100;
    for(int i = 0 ; i < length ; i++) {
        write_sized_char( message[i],  x + i*spacing*size, y, color, black, size);
    }
}

Game* pseudo_game( Game* saved_game ){
  
    if( saved_game == NULL){
        start_game();
    }
    else{
        game = saved_game;
    }

    char welcome_message[] = "Press [SPACE] to start! [X] to exit!";
    print_message(welcome_message, 37, white);

    while((c = getchar()) != ' ' && c != 'x');
        if (c == 'x') return;

    while( !game->game_over ){
        game_refresh();
    }

    return game;
}
