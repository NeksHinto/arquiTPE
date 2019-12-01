#include <shell.h>
#include <video_module.h>
#include <sound_module.h>
#include <time_module.h>
#include <syscall.h>
#include <font.h>
#include <stdio.h>
#include <stdlib.h>
#include <error_handler.h>
#include <exception_tester.h>
#include <pseudo_game.h>

#define HORIZONTAL_MARGIN 2
#define VERTICAL_MARGIN 0
#define STDOUT 1
#define STDERR 2
#define MAX_SIZE 255
#define ESC 27

static const Color BLACK = {0, 0, 0};
static const Color RED = {255, 0, 0};
static const Color GREEN = {0, 255, 0};
static const Color BLUE = {0, 0, 255};
static const Color WHITE = {255, 255, 255};
static const char* starting_tag = "~>";
static Color BACKGROUND_COLOR;
static Color TEXT_COLOR;

static int MAX_LINE_POSITION_X;
static int MAX_LINE_POSITION_Y;
static char buffer[20000];
static int buffer_index = 0;


static int line_y_value=VERTICAL_MARGIN;
static int line_x_value=HORIZONTAL_MARGIN;

static Game aracnoid = {.game_over = TRUE};



void init();
void consoleLoop();
void refresh_stdin();

static void write_tag();
static void set_cursor();
static void new_line();
static int invalid_position_x();
static int invalid_position_y();
static void reset_x_position ();
static void reset_y_position();
static void refresh_buffer();
static void clear_buffer();
static void clear_screen();

static void command_dispatcher(char *buffer);
static void help();

void start_shell(){
  init();
  consoleLoop();
}

void init(){
  MAX_LINE_POSITION_X = (get_screen_width()-HORIZONTAL_MARGIN*WIDTH);
  MAX_LINE_POSITION_Y = (get_screen_height()-VERTICAL_MARGIN*HEIGHT);
  TEXT_COLOR = WHITE;
  BACKGROUND_COLOR = BLACK;
  char* to_print = "Write 'help' to see a list of commands!";
  printf("%s\n", to_print);
}


void consoleLoop(){
  refresh_buffer(STDOUT);
  refresh_buffer(STDERR);
  while(1){
    refresh_stdin();
    refresh_buffer(STDOUT);
    refresh_buffer(STDERR);
  }
}

void refresh_stdin(){
  buffer_index=0;
  write_tag();
  char c;
  while((c = getchar()) != '\n' && c != ESC){
    if(c=='\b'){
      if(buffer_index!=0){
        if(line_x_value <= HORIZONTAL_MARGIN){
          line_y_value--;
          line_x_value= (MAX_LINE_POSITION_X / ((WIDTH + 1))) ;
        }
        else
          line_x_value--;

        buffer_index--;
        buffer[buffer_index] = 0;
        write_block(line_x_value*(WIDTH+1), line_y_value*HEIGHT, WIDTH+1, HEIGHT, BACKGROUND_COLOR);
      }
    }
    else if(c){
      set_cursor();
      buffer[buffer_index++] = c;
      write_char(c, line_x_value*(WIDTH + 1), line_y_value * HEIGHT, TEXT_COLOR);
      line_x_value++;
    }
  }
  if(c == ESC){
      clear_screen();
      aracnoid = pseudo_game(aracnoid);
      clear_screen();
      clear_buffer();
  }
  else{
      new_line();
      command_dispatcher(buffer);
      clear_buffer();
  }

}

static void refresh_buffer(int buffer) {
  int flag=0;
  char c;
  while((c=getchar_from_buffer(buffer))!=0){
    flag=1;
    if(c == '\n'){
      new_line();
    }
    else{
      set_cursor();
      Color aux = TEXT_COLOR;
      if(buffer == 2)
        aux = RED;
      write_char(c, line_x_value*(WIDTH + 1), line_y_value*HEIGHT, aux);
      line_x_value++;
    }
  }
  if(flag)
    new_line();
}

static void set_cursor() {
  if(invalid_position_x())
    new_line();
}
static void write_tag() {
  const char * text = starting_tag;
  while(*text){
    write_char(*text, line_x_value*(WIDTH + 1), line_y_value*HEIGHT, GREEN );
    line_x_value++;
    text++;
  }
}
static void new_line() {
  if(invalid_position_y()){
    move_screen_up(HEIGHT, BACKGROUND_COLOR);
    line_y_value--;
  }
  line_y_value++;
  reset_x_position();
}
static int invalid_position_x() {
  return (line_x_value) * (WIDTH + 1) > MAX_LINE_POSITION_X;
}
static int invalid_position_y() {
  return (line_y_value) * (HEIGHT +1) > MAX_LINE_POSITION_Y;
}
static void reset_x_position () {
  line_x_value = HORIZONTAL_MARGIN;
}

static void reset_y_position() {
  line_y_value = VERTICAL_MARGIN;
}

static void clear_buffer() {
  for(int i = 0; i < buffer_index; i++)
    buffer[i] = 0;
  buffer_index = 0;
}




static void command_dispatcher(char *buffer) {
  int i,j;
  char command[MAX_SIZE] = {0};
  char parameter[MAX_SIZE] = {0};
  int reading_command = 1;

  for(i = 0, j = 0; buffer[i] != 0 && i < MAX_SIZE - 1 && j < MAX_SIZE - 1; i++){
      if(buffer[i] == ' ' && reading_command){
          reading_command = 0;
          command[i] = 0;
      }
      else if(reading_command)
          command[i] = buffer[i];
      else
          parameter[j++] = buffer[i];

  }
  if(strcmp(command, "help")){
    help();
    return;
  }
  if(strcmp(command, "clear")){
    clear_screen();
    return;
  }
  if(strcmp(command, "beep")){
    int flag = 1;
    for(int i=0; parameter[i] != '\0' && flag; i++)
        flag = isdigit(parameter[i]);
    if(flag)
      beep(atoi(parameter));
    else
      send_error("Invalid parameter");
    return;
    }
  if(strcmp(command, "width")) {
    printf("%d", get_screen_width());
    return;
  }
  if(strcmp(command, "height")){
    printf("%d", get_screen_height());
    return;
  }
  if(strcmp(command, "echo")){
    printf(parameter);
    return;
  }
  if(strcmp(command, "time")) {
    int hour = system_hours();
    if(hour < 3){
      hour = 24 - hour;
    }else{
      hour -= 3; 
      // Chequear que esto sea correcto, capaz con -9 funcione.
    }
    
    char hours[3];
    itoa(hour, 16, hours);
    if(strlen(hours) == 1){
      hours[1] = hours[0];
      hours[0] = '0';
    }
    char minutes[3];
    itoa(system_minutes(), 16, minutes);
    if(strlen(minutes) == 1){
      minutes[1] = minutes[0];
      minutes[0] = '0';
    }
    char seconds[3];
    itoa(system_seconds(), 16, seconds);
    if(strlen(seconds) == 1){
      seconds[1] = seconds[0];
      seconds[0] = '0';
    }
    printf("%s:%s:%s", hours, minutes, seconds);
    return;
  }
  if(strcmp(command, "div0")) {
    clear_screen();
    _division_by_zero();
    return;
  }
  if(strcmp(command, "invOp")) {
    clear_screen();
    _invalid_op_code();
    return;
  }
  if(strcmp(command, "aracnoid")) {
      aracnoid.game_over = TRUE;
      clear_screen();
      aracnoid = pseudo_game(aracnoid);
      clear_screen();
      return;
  }
  if(strcmp(command, "printMem")){
      char *str = "123456789 HELLO WORLD 123456789A";
      struct  s {
          int nums[6];
          char c1;
          char c2;
          char c3;
          char c4;
          char c5;
          char c6;
          char c7;
          char c8;

      }s;
      for(int i = 0; i < 27; i++)
          s.nums[i] = i+1;
      s.c1 = 'H';
      s.c2 = 'E';
      s.c3 = 'L';
      s.c4 = 'L';
      s.c5 = 'O';
      s.c6 = '!';
      s.c7 = '!';
      s.c8 = '!';
      clear_screen();
      printf("str = %d --> \"123456789 HELLO WORLD 123456789A\"\n\n", str);
      printMem(str);
      printf("\n############################################################\n\n");
      printf("&struct = %d --> \"\n{\n", &s);
      printf("\t\t\tint nums[6] = { 1 2 3 4 5 6 }\n");
      printf("\t\t\tchar c1 = 'H'\n");
      printf("\t\t\tchar c2 = 'E'\n");
      printf("\t\t\tchar c3 = 'L'\n");
      printf("\t\t\tchar c4 = 'L'\n");
      printf("\t\t\tchar c5 = 'O'\n}\"\n");

      printMem(&s);
      printf("\n############################################################\n\n");
      return;
  }
  
  send_error("Unrecognized command.");
}

static void help() {
    printf("Commands:\n");
    printf("\thelp -- Shows available commands.\n");
    printf("\tclear -- Clears the screen.\n");
    printf("\tbeep num -- Receives an number as a parameter and beeps for that amount of ticks.\n");
    printf("\techo string -- Recieves a string as parameter and repeats it as output\n");
    printf("\twidth -- Shows the screen width.\n");
    printf("\theight -- Shows the screen height.\n");
    printf("\tdiv0 -- Tests division by zero exception.\n");
    printf("\tinvOp -- Tests invalid op code exception.\n");
    printf("\ttime -- Shows the current system time.\n");
    printf("\taracnoid -- Opens the aracnoid game.\n\t\tPlayer moves with [W] and [S]\n\t\tPress [X] to exit or [ESC] to pause game.\n");
    printf("\tprintMem -- Makes a memory dump of the first 32 bytes from the given address\n");

}

static void clear_screen() {
  fill_screen( BACKGROUND_COLOR);
  reset_x_position();
  reset_y_position();
}
