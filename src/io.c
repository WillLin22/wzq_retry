#include "eval.h"
#include "state.h"
#include <io.h>
#include <stdio.h>
#include <log.h>

static int lower(int c)
{
    if('a' <= c && c <= 'z')
        return c;
    else
        return c - 'A' + 'a';
}

static int getnum(int first, int* val)
{
    int c, res = first - '0';
    while(isdigit(c = getchar()))
    {
        log(DEBUG, "%s: get %c as next input\n", __func__, c);
        res = res * 10 + c - '0';
    }
    *val = SIZE - res;
    return c;
}

int input_place(Point* pos)
{
    printf("Please enter where you want to place:\n");
    int c = getchar(), x_assigned = 0, y_assigned = 0;
    while(c != '\n' && c != EOF)
    {
        if(isalpha(c) &&!y_assigned)
        {
            pos->y = lower(c) - 'a';
            y_assigned = 1;
            c = getchar();
        }
        else if(isdigit(c) &&!x_assigned)
        {
            c = getnum(c, &pos->x);
            x_assigned = 1;
        }
        else
            goto error;
        
    }
    if(c == EOF)
        return EOF;
    if(!x_assigned || !y_assigned)
        goto error;
    return 0;
error:
    printf("Error: invalid input!\n");
    while(c != '\n' && c != EOF)
        c = getchar();
    return 1;
}


void print_over(GameState* state)
{
    if(state->score < WIN && state->score > -WIN)
    {
        log(ERROR, "%s: You should not enter this with score %d!", __func__ ,state->score);
        return ;
    }
    printf("%s wins!\n", state->score >= WIN ? "BLACK" : "WHITE");
}

