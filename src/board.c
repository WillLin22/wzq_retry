#include "state.h"
#include<board.h>
#include<log.h>

char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE] = 
{
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
		". . . . . . . . . . . . . . .",
};

char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic='x';//黑棋子;
char play1CurrentPic='+'; 

char play2Pic='o';//白棋子;
char play2CurrentPic='*';

char Pics[PIC_RECORD_TOTAL];

int arrayForInnerBoardLayout[SIZE][SIZE];

void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);

static int current_to_past(Point pos)
{
	if(arrayForInnerBoardLayout[pos.x][pos.y] == BLACK_CURRENT)
		arrayForInnerBoardLayout[pos.x][pos.y] = BLACK;
	else if(arrayForInnerBoardLayout[pos.x][pos.y] == WHITE_CURRENT)
		arrayForInnerBoardLayout[pos.x][pos.y] = WHITE;
	else
	{
		log(ERROR, "%s:"POS_FMT_STR" is not current!\n", __func__, POS_FMT(pos.x, pos.y));
		return 1;
	}
	return 0;
}
static int isvalid(Point pos)
{
	if(pos.x < 0 || pos.x >=SIZE || pos.y < 0 || pos.y >= SIZE)
		return 1;
	if(arrayForInnerBoardLayout[pos.x][pos.y] != EMPTY)
		return 2;
	return 0;
} 
void board_init()
{
	Pics[BLACK] = play1Pic;
	Pics[WHITE] = play2Pic;
	Pics[BLACK_CURRENT] = play1CurrentPic;
	Pics[WHITE_CURRENT] = play2CurrentPic;
	initRecordBorard();
}

void board_display()
{
	innerLayoutToDisplayArray();
	displayBoard();
}

int board_place(Point pos, GameState *state)
{
	int status = isvalid(pos);
	if(status != 0)
	{
		if(status == 2)
			printf("Error: This place has already been placed!  "POS_FMT_STR"\n", POS_FMT(pos.x, pos.y));
		if(status == 1)
			printf("Error: Input out of range!\n");
		return 1;
	}
	Pic pic = state->currentPlayer == BLACK ? BLACK_CURRENT : WHITE_CURRENT;
	arrayForInnerBoardLayout[pos.x][pos.y] = pic;
	current_to_past(state->last_place);
	gamestate_place(state, pos);
	gamestate_turn_update(state);
	return 0;
}

//初始化一个空棋盘格局 
void initRecordBorard(void){
	memset(arrayForInnerBoardLayout, 0, sizeof(arrayForInnerBoardLayout));
}


//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void){
	for(int i = 0; i < SIZE; i++)
	{
		strcpy(arrayForDisplayBoard[i], arrayForEmptyBoard[i]);
		for(int j = 0; j < SIZE; j++)
		{
			if(arrayForInnerBoardLayout[i][j] != 0)
				arrayForDisplayBoard[i][j*CHARSIZE] = Pics[arrayForInnerBoardLayout[i][j]];
		}
	}

}


//显示棋盘格局 
void displayBoard(void){
	int i;
	//第一步：清屏
	system("clear");   //清屏  
	//第二步：将arrayForDisplayBoard输出到屏幕上
	for(int i = 0; i < SIZE; i++)
		printf("%2d %s\n", SIZE - i, arrayForDisplayBoard[i]);
	
	//第三步：输出最下面的一行字母A B .... 
	printf("   ");
	for(int i = 0; i < SIZE; i++)
		printf("%c ", 'A' + i);
	printf("\n");
} 

