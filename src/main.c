#include <state.h>
#include <board.h>
#include <input.h>
#include <log.h>
#include <stdio.h>



int main()

{
    board_init();
    gamestate_init(&state);
    while(1)
    {
        Point pos;
        board_display();
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
    }

    return 0;
}


