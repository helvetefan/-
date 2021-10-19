#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "block.h"
#include "테트리스.h"

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20
#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2
#define ESC 27 
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

int speed,block_id,score;
int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];

void DrawGameBoard();
void ProcessKeyInput();
void BlockUp(); int BlockDown(); void ShiftLeft(); void ShiftRight();
void OneEightyRotateBlock(); void CounterRotateBlock(); void RotateBlock();
void RedrawBlocks(void);    void SpaceDown();   void AddBlockToBoard(void); int isGameOver();
void RemoveFillupLine();    void PrintScore();
    
int main(void)
{
    int ran, x, y;
    COORD curPos = GetCurrentCursorPos();

    speed = 5, score = 0;

    for (y = 0; y < GBOARD_HEIGHT; ++y) {
        gameBoardInfo[y][0] = 1;
        gameBoardInfo[y][GBOARD_WIDTH+1] = 1;
    }
    
    for (x = 0; x < GBOARD_WIDTH + 2; ++x) {
        gameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }

    RemoveCursor();
    srand((unsigned int)time(NULL));

    ran = rand() % 4;
    block_id = (rand() % 7) * 4 + ran;

    DrawGameBoard();

    PrintScore();

    while (1) {
        gotoxy(GBOARD_ORIGIN_X + GBOARD_WIDTH, 0);
        if (isGameOver()) {
            printf("GAME OVER");
            break;
        }

        ran = rand() % 4;
        block_id = (rand() % 7) * 4 + ran;

        while (1) {
            if (BlockDown() == 0) {
                AddBlockToBoard();
                RemoveFillupLine();
                PrintScore();
                break;
            }
            ProcessKeyInput();
        }
    }
    return 0;
}

int DetectCollision(int posX, int posY, char blockModel[4][4]) {
    int arrX = (posX - GBOARD_ORIGIN_X) / 2;
    int arrY = (posY - GBOARD_ORIGIN_Y);
    int x, y;

    for (y = 0; y < 4; ++y) {
        for (x = 0; x < 4; ++x) {
            if (blockModel[y][x] && gameBoardInfo[arrY + y][arrX + x])
                return 1;
        }
    }
    
    return 0;
}
void ProcessKeyInput() {
    int i;
    char key;

    for (i = 0; i < 20; ++i) {
        if (_kbhit()) {
            key = _getch();
            switch (key) {
            case LEFT:
                ShiftLeft();
                break;
            case RIGHT:
                ShiftRight();
                break;
            case UP:
                CounterRotateBlock();
                break;
            case SPACE:
                SpaceDown();
                break;
            }
        }
        Sleep(speed);
    }
}
void DrawGameBoard() {
    int x, y;
    for (y = 0; y <= GBOARD_HEIGHT; ++y) {
        gotoxy(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        
        if (y == GBOARD_HEIGHT)
            printf("└");
        else
            printf("│");
    }
    for (y = 0; y <= GBOARD_HEIGHT; ++y) {
        gotoxy(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);

        if (y == GBOARD_HEIGHT)
            printf("┘");
        else
            printf("│");
    }
    for (x = 1; x < GBOARD_WIDTH + 1; ++x) {
        gotoxy(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("─");
    }

    gotoxy(GBOARD_ORIGIN_X + GBOARD_WIDTH, 0);
}
void ShiftRight()
{
    COORD curPos = GetCurrentCursorPos();

    if (DetectCollision(curPos.X + 2, curPos.Y, blockModel[block_id]))
        return;

    DeleteBlock(blockModel[block_id]);
    curPos.X += 2;
    gotoxy(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
}
void ShiftLeft()
{
    COORD curPos = GetCurrentCursorPos();

    if (DetectCollision(curPos.X - 2, curPos.Y, blockModel[block_id]))
        return;

    DeleteBlock(blockModel[block_id]);
    curPos.X -= 2;
    gotoxy(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
}
int BlockDown()
{
    COORD curPos = GetCurrentCursorPos();

    if (DetectCollision(curPos.X, curPos.Y + 1, blockModel[block_id]))
        return 0;

    DeleteBlock(blockModel[block_id]);
    curPos.Y++;
    gotoxy(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
    return 1;
}
void BlockUp()
{
    COORD curPos = GetCurrentCursorPos();

    DeleteBlock(blockModel[block_id]);
    curPos.Y--;
    gotoxy(curPos.X, curPos.Y);
    ShowBlock(blockModel[block_id]);
}
void CounterRotateBlock() {// 위 delete & 아래 show
    int block_senior = block_id - block_id % 4;
    int block_rotated = block_senior + (block_id + 1) % 4;
    COORD curPos = GetCurrentCursorPos();

    if (DetectCollision(curPos.X, curPos.Y, blockModel[block_rotated]))
        return;

    DeleteBlock(blockModel[block_id]);
    block_id = block_rotated;
    ShowBlock(blockModel[block_id]);

}
void RotateBlock() {// 위 delete & 아래 show
    int block_senior = block_id - block_id % 4;
    int block_rotated = block_senior + (block_id + 1) % 4;
    COORD curPos = GetCurrentCursorPos();

    if (DetectCollision(curPos.X, curPos.Y, blockModel[block_rotated]))
        return;

    DeleteBlock(blockModel[block_id]);
    block_id = block_rotated;
    ShowBlock(blockModel[block_id]);

}
void OneEightyRotateBlock() {// 위 delete & 아래 show
    int block_senior = block_id - block_id % 4;
    int block_rotated = block_senior + (block_id + 1) % 4;
    COORD curPos = GetCurrentCursorPos();

    if (DetectCollision(curPos.X, curPos.Y, blockModel[block_rotated]))
        return;

    DeleteBlock(blockModel[block_id]);
    block_id = block_rotated;
    ShowBlock(blockModel[block_id]);

}
void RedrawBlocks(void)
{
    int x, y;
    int cursX, cursY;
    for (y = 0; y < GBOARD_HEIGHT; y++)
    {
        for (x = 1; x < GBOARD_WIDTH + 1; x++)
        {
            cursX = x * 2 + GBOARD_ORIGIN_X;
            cursY = y + GBOARD_ORIGIN_Y;
            gotoxy(cursX, cursY);
            if (gameBoardInfo[y][x] == 1)
            {
                printf("■");
            }
            else { printf("  "); }
        }
    }
}
void SpaceDown() {
    COORD curPos = GetCurrentCursorPos();

    while (BlockDown());
}
void AddBlockToBoard(void) {
    COORD curPos = GetCurrentCursorPos();
    int arrX, arrY, x, y;

    for (y = 0; y < 4; ++y) {
        for (x = 0; x < 4; ++x) {
            arrX = (curPos.X - GBOARD_ORIGIN_X) / 2;
            arrY = (curPos.Y - GBOARD_ORIGIN_Y);


            if (blockModel[block_id][y][x])
                gameBoardInfo[arrY + y][arrX + x] = 1;
        }
    }
}
int isGameOver() {
    COORD curPos = GetCurrentCursorPos();
    if (DetectCollision(curPos.X, curPos.Y, blockModel[block_id]))
        return 1;
    return 0;
}
void RemoveFillupLine() {
    int line, x, y,i;

    for (i = 0; i < 4; ++i) {
        for (y = GBOARD_HEIGHT - 1; y > 0; --y) {
            for (x = 1; x < GBOARD_WIDTH + 1; ++x) {
                if (gameBoardInfo[y][x] != 1)
                    break;
            }

            if (x == GBOARD_WIDTH + 1) {
                for (line = 0; line < y; ++line) {
                    memcpy(&gameBoardInfo[y - line][1], &gameBoardInfo[y - line - 1][1], GBOARD_WIDTH * sizeof(int));
                }
                score += 10;
            }
        }
    }
    RedrawBlocks();
}
void PrintScore() {
    gotoxy((GBOARD_WIDTH + GBOARD_ORIGIN_X) * 2 , GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2);
    printf("SCORE : %d", score);
}