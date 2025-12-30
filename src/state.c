#include "board.h"
#include <state.h>
#include <eval.h>

GameState state;

void gamestate_init(GameState* state)
{
    memset(state, 0, sizeof(GameState));
    state->currentPlayer = BLACK;
    state->current_place = (Point){-1, -1};
}

void gamestate_turn_update(GameState *state)
{
    int next = state->currentPlayer == BLACK ? WHITE : BLACK;
    state->currentPlayer = next;
}
void gamestate_place(GameState* state, Point pos)
{
    gamestate_turn_update(state);
    state->current_place = pos;
    state->score = evaluation(arrayForInnerBoardLayout, state);
}
