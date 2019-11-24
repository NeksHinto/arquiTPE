#ifndef PSEUDO_GAME_H
    #define PSEUDO_GAME_H

#define FALSE 0
#define MAX_BLOCKS 2
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
    int height,width;
    Color color;
} Entity;

typedef struct Game {
    Entity blocks[MAX_BLOCKS];
    Entity ball;
    Entity player;
    int game_over;
    int blocks_q;
} Game;

typedef Game* GameADT;

GameADT  pseudo_game();


#endif

