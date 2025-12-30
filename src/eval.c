#include "board.h"
#include "state.h"
#include <eval.h>

#include <log.h>
#include <stdlib.h>


typedef enum{
    ROW, COL, DIAG1, DIAG2, DIR_TOTAL
}Dirs;

static Pic get_pic(int board[SIZE][SIZE], Point pos)
{
    int x = pos.x, y = pos.y;
    if(x < 0 || y < 0 || x > SIZE || y > SIZE)
        return INVALID;
    return board[x][y];
}

// The recordboard is used to record patterns that is centered with pos. 
// The caller should guarantee that the recordboard has at least DIR_TOTAL*(2*scan_radius+1)*sizeof(int) for recording
static void scan(int board[SIZE][SIZE], Point pos, int scan_radius, int** recordboard)
{
    int x = pos.x, y = pos.y;
    for(int k = -scan_radius; k <= scan_radius; k++)
    {
        recordboard[ROW][k+scan_radius] = get_pic(board, (Point){x, y+k});
        recordboard[COL][k+scan_radius] = get_pic(board, (Point){x+k, y});
        recordboard[DIAG1][k+scan_radius] = get_pic(board, (Point){x+k, y+k});
        recordboard[DIAG2][k+scan_radius] = get_pic(board, (Point){x-k, y+k});
    }
}

static int win_match(int** record, int scan_radius)
{
    if(2*scan_radius + 1 < 5)
    {
        log(ERROR, "%s: The scan_radius %d is not large enough to contain pattern equal or longer than 5!", __func__, scan_radius);
        return 0;
    }
    int dirs[DIR_TOTAL];
    memset(dirs, 0, sizeof(dirs));
    for(int dir = 0; dir < DIR_TOTAL; dir++)
        for(int k = -scan_radius; k <= scan_radius - 4; k++)
        {
            int res = -1;
            for(int index = k + scan_radius; index <= k + scan_radius + 4; index++)
                res &= record[dir][index];
            dirs[dir] |= res;
        }
    int res = 0;
    for(int dir = 0; dir < DIR_TOTAL; dir++)
        res |= dirs[dir];
    if(res >= PIC_RECORD_TOTAL)
    {
        log(ERROR, "%s: Multiple winner detected! res:%d", __func__, res);
        return 0;
    }
    return res == BLACK ? WIN : res == WHITE ? -WIN : 0;
}
// 复杂变量的使用
static int (*checkers[])(int**, int) = {win_match};

int evaluation(int board[SIZE][SIZE], GameState *state)
{
    int scan_radius = 4;
    int score = 0;
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            if(board[i][j] != EMPTY)
            {
                int record_len = 2*scan_radius+1;
                int *recordboard = (int*)malloc(DIR_TOTAL*record_len*sizeof(int));
                int *recordp[DIR_TOTAL];
                for(int dir = 0; dir < DIR_TOTAL; dir++)
                    recordp[dir] = &recordboard[dir*record_len];
                scan(board, (Point){i, j}, scan_radius, recordp);

                // 以下是对所有负责pattern匹配的函数的封装，这样当需要实现新的匹配函数仅需要在
                // 函数数组中添加元素即可而无需修改evaluation 函数代码。
                int tot_checkers = sizeof(checkers)/sizeof(int*);
                for(int k = 0; k < tot_checkers; k++)
                    score += checkers[k](recordp, scan_radius);
                free(recordboard);
            }
    return score;
}