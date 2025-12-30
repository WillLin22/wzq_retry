#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//保证非EMPTY的每一种情况都只占独立bit
typedef enum Pic{
    EMPTY = 0, BLACK, WHITE, INVALID = 4, PIC_RECORD_TOTAL
}Pic;

typedef struct Point{
    int x, y;
}Point;

typedef struct GameState{
    int currentPlayer;
    Point current_place;
    int score;
}GameState;

extern GameState state;

void gamestate_init(GameState* state);
void gamestate_place(GameState* state, Point pos);
static inline Point gamestate_getcurrent(GameState* state)
{
    return state->current_place;
}
static inline int gamestate_getscore(GameState* state)
{
    return state->score;
}


#endif