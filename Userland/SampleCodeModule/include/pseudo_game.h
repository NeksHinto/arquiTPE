#ifndef PSEUDO_GAME_H
    #define PSEUDO_GAME_H

#define FALSE 0
#define MAX_BLOCKS 18
#define TRUE !FALSE
#define NULL 0

typedef struct Position {
    int x,y;
} Position;

typedef struct Speed {
    int x,y;
} Speed;

typedef struct Entity {
    Position position;
    Speed speed;
    int height,width, visible;
    Color color;
} Entity;

typedef struct Game {
    Entity blocks[MAX_BLOCKS];
    Entity ball;
    Entity player;
    int game_over;
    int remaining_blocks;
} Game;

typedef Game* GameADT;

Game  pseudo_game();


#endif

