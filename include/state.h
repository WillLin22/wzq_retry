#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum Pic{
    EMPTY = 0, BLACK, WHITE, BLACK_CURRENT, WHITE_CURRENT, PIC_RECORD_TOTAL
}Pic;

typedef struct Point{
    int x, y;
}Point;

typedef struct GameState{
    int currentPlayer;
    Point last_place;
}GameState;

extern GameState state;

void gamestate_init(GameState* state);
void gamestate_place(GameState* state, Point pos);
void gamestate_turn_update(GameState* state);


#endif