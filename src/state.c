#include <state.h>

GameState state;

void gamestate_init(GameState* state)
{
    state->currentPlayer = BLACK;
    state->last_place = (Point){-1, -1};
}

void gamestate_place(GameState* state, Point pos)
{
    state->last_place = pos;
}

void gamestate_turn_update(GameState *state)
{
    int next = state->currentPlayer == BLACK ? WHITE : BLACK;
    state->currentPlayer = next;
}