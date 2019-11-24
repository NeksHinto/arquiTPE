
#include <font.h>
#include <video_module.h>
#include <stdio.h>
#include <sound_module.h>
#include <time_module.h>


typedef struct Player{
	int x;
  int y;
  int score;
} p_t;

typedef struct Ball{
	int x;
  int y;
  int vert;
  int hori;
} b_t;

typedef p_t * Player;
typedef b_t * Ball;

#define BALL_SPEED 14
#define PLAYER_SPEED 5
#define BALL_RADIO 8


#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 200


#define BOARD_WIDTH 12



#define SCORELINE_HEIGHT 20
#define SCORELINE_WIDTH 10
#define SCORELINE_SPACE 10
#define SCORE_SIZE 10
static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;
static int PLAYER_TOP; 
static int MIDDLE_X;
static int MIDDLE_Y;

static const Color white = {225,225,225};
static const Color black = {0,0,0};
static const Color blue = {70,130,226};
static const Color red = {221,53,75};

static void draw_middle_line();
static void refresh_screen();
static void draw_players(Player player, Color color);
static void draw_ball(Color color);
static void draw_scores(Color color);
static void move_ball();
static void wait_for_space();
static void score(Player scorer);
static void start_again();
static void player_move(Player player, int direction);
static void draw_board();
static void init_game(void);
static void draw_circle(int x, int y, int radio, Color color);

#define UP -1
#define DOWN 1

static Player p1;
static Player p2;
Ball ball;

int total_score = 0;
int score_flag = 0;


static void draw_circle(int x, int y, int radio, Color color){
  for(int i = -radio; i <= radio; i++){
    for(int j = -radio; j <= radio; j++){
      if(i*i + j*j <= radio*radio){
        write_pixel(x+i, y+j, color);
      }
    }
  }
}

static void init_game(void){
  SCREEN_WIDTH = get_screen_width();
  SCREEN_HEIGHT = get_screen_height();
  PLAYER_TOP = SCREEN_HEIGHT - PLAYER_HEIGHT;
  MIDDLE_X = SCREEN_WIDTH/2;
  MIDDLE_Y = SCREEN_HEIGHT/2;
  draw_board();
}

void game(){
  init_game();
  p_t aux1 = {BOARD_WIDTH, MIDDLE_Y - PLAYER_HEIGHT/2, 0};
  p1 = &aux1;
  p_t aux2 = { SCREEN_WIDTH - PLAYER_WIDTH - BOARD_WIDTH, MIDDLE_Y - PLAYER_HEIGHT/2, 0};
  p2 = &aux2;
  b_t aux3 = {MIDDLE_X, MIDDLE_Y,BALL_SPEED, BALL_SPEED};
  ball = &aux3;

  draw_scores(white);
  refresh_screen();
  wait_for_space();
  draw_scores(black);
 char c;
  
  int old_ticks = 0;
  while((c = getchar()) != 'x'){
    
    int ticks = ticks_elapsed();
    if(c == 'w' || c == 'W') {
      player_move(p1, UP);
    }else if(c == 's' || c == 'S') {
      player_move(p1, DOWN);
    }else if(c == 'o' || c == 'O') {
      player_move(p2, UP);
    }else if(c == 'l' || c == 'L') {
      player_move(p2, DOWN);
    }
    draw_middle_line();
    if(old_ticks + 1 < ticks){
      move_ball();
      old_ticks = ticks;
    }
  }
}

static void draw_board(){
  fill_screen(black);
  write_block(0, 0, SCREEN_WIDTH, 2, white);
  write_block(0, SCREEN_HEIGHT-2, SCREEN_WIDTH, 2, white);
  write_block(MIDDLE_X -2, 0, 2, SCREEN_HEIGHT, white);
  refresh_screen();
}

static void player_move(Player player, int direction){
  
  draw_players(player, black);
  int next_pos = player->y + direction*PLAYER_SPEED;
  //+-3 to avoid collision with top and bottom lines.
  if(next_pos < 0 + 3){
    player->y = 0 + 3;
  }
  else if(next_pos > PLAYER_TOP - 3){
    player->y = PLAYER_TOP - 3;
  }
  else
    player->y = next_pos;
  draw_players(player, white);
}



static void move_ball(){
  score_flag = 0;
  draw_ball(black);
  //ball hits top or bottom of the screen.
  if ((ball->y) - BALL_RADIO <= 0 + BOARD_WIDTH || (ball->y) + BALL_RADIO >= SCREEN_HEIGHT - BOARD_WIDTH) { 
    ball->vert = (ball->vert)*-1;
    write_block(0, 0, SCREEN_WIDTH, 2, white);
    write_block(0, SCREEN_HEIGHT-2, SCREEN_WIDTH, 2, white);
    beep(1);
  }
  //ball reaches the left limit.
  if ((ball->x)-BALL_RADIO <= PLAYER_WIDTH + BOARD_WIDTH ) { 
    if (ball->y >= p1->y + PLAYER_HEIGHT || ball->y <= p1->y) {
      score(p2);
    } 
    else {
      ball->hori = (ball->hori)*-1;
      beep(1);
    }
    draw_players(p1, white);
  }
  //ball reaches the right limit.
  if ((ball->x)+ BALL_RADIO >= SCREEN_WIDTH - PLAYER_WIDTH - BOARD_WIDTH ) {
    if (ball->y >= p2->y + PLAYER_HEIGHT || ball->y <= p2->y ) {
      score(p1);
    } 
    else {
      ball->hori = (ball->hori)*-1;
      beep(1);
    }
    draw_players(p2, white);
  }

  if (!score_flag) {
    
    ball->x = ball->x + ball->hori;
    ball->y = ball->y + ball->vert;
    draw_ball(white);
  }
}

static void start_again() {
  wait_for_space();
  draw_scores(black);
  ball->x = MIDDLE_X;
  ball->y = MIDDLE_Y;
}

static void score(Player scorer) {
  beep(5);
  scorer->score = scorer->score + 1;
  draw_scores(white);
  start_again();
}

static void draw_middle_line() {
  write_block(MIDDLE_X -2, 0, 2, SCREEN_HEIGHT, white);
}

static void refresh_screen() {
  draw_players(p1, white);
  draw_players(p2, white);
  draw_ball(white);
}

static void draw_players(Player player, Color color){
  write_block(player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT, color);
}

static void draw_ball(Color color){
  draw_circle(ball->x, ball->y, BALL_RADIO, color);
}

static void draw_scores(Color color) {
  int p1_score, p2_score;
  p1_score = p1->score;
  p2_score = p2->score;

  int p1_right = p1_score %10;
  int p1_left = p1_score /10;
  int p2_right = p2_score %10;
  int p2_left = p2_score /10;

  write_sized_char( p1_left + '0',  MIDDLE_X - BOARD_WIDTH - 2*SCORE_SIZE*WIDTH, BOARD_WIDTH + SCORELINE_HEIGHT, color, black, SCORE_SIZE);
  write_sized_char( p1_right + '0',  MIDDLE_X - BOARD_WIDTH - SCORE_SIZE*WIDTH, BOARD_WIDTH + SCORELINE_HEIGHT, color, black, SCORE_SIZE);


  write_sized_char( p2_left + '0',  MIDDLE_X + BOARD_WIDTH, BOARD_WIDTH + SCORELINE_HEIGHT, color, black, SCORE_SIZE);
  write_sized_char( p2_right + '0',  MIDDLE_X + BOARD_WIDTH + SCORE_SIZE*WIDTH, BOARD_WIDTH + SCORELINE_HEIGHT, color, black, SCORE_SIZE);
}

static void wait_for_space() {
  char c;
  while((c = getchar()) != ' ');
}