#ifndef BOARD_H
#define BOARD_H


#include <state.h>
#define SIZE 15
#define CHARSIZE 2
#define POS_FMT_STR "%c%-2d"
#define POS_FMT(posx, posy) (posy + 'A'), (SIZE - posx)


//空棋盘模板 
extern char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE];
//此数组存储用于显示的棋盘 
extern char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
extern char play1Pic;//黑棋子;
extern char play1CurrentPic; 

extern char play2Pic;//白棋子;
extern char play2CurrentPic;

//此数组用于记录当前的棋盘的格局 
extern int arrayForInnerBoardLayout[SIZE][SIZE];

// 初始化棋盘
void board_init();
// 打印当前棋盘
void board_display();
// 落子
int board_place(Point pos, GameState* state);


#endif