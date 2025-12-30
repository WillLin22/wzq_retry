#include <state.h>
#include <board.h>
#include <io.h>
#include <eval.h>
#include <log.h>
#include <stdio.h>



int main()

{
    board_init();
    gamestate_init(&state);
    board_display();
    while(1)
    {
        Point pos;
        int status;
        while(1)
        {
            status = input_place(&pos);
            if(status == EOF)
                return 0;
            if(status != 0 || board_place(pos, &state) != 0)
                continue;
            break;
        }
        board_display();
        int score = gamestate_getscore(&state);
        if(score >= WIN || score <= -WIN)
        {
            print_over(&state);
            break;
        }
    }

    return 0;
}


