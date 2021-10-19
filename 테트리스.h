#include <stdio.h>
#include <Windows.h>
#include "block.h"

void gotoxy(int x, int y);  COORD GetCurrentCursorPos(void);
void RemoveCursor(void);
void ShowBlock(char blockinfo[4][4]);   void DeleteBlock(char blockinfo[4][4]);

void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD GetCurrentCursorPos(void) {
    COORD curPoint;
    CONSOLE_SCREEN_BUFFER_INFO curInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); //curinfo 에 현재 커서위치 저장
    curPoint.X = curInfo.dwCursorPosition.X;
    curPoint.Y = curInfo.dwCursorPosition.Y;

    return curPoint;
}

void RemoveCursor(void) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void ShowBlock(char blockinfo[4][4]) {        
    int x, y;
    COORD curPos = GetCurrentCursorPos();

    for (y = 0; y < 4; ++y) {
        for (x = 0; x < 4; ++x) {
            gotoxy(curPos.X + (x * 2), curPos.Y + y);

            if (blockinfo[y][x])
                printf("■");
        }
    }
    gotoxy(curPos.X, curPos.Y);
}

void DeleteBlock(char blockinfo[4][4]) {
    int x, y;
    COORD curPos = GetCurrentCursorPos();

    for (y = 0; y < 4; ++y) {
        for (x = 0; x < 4; ++x) {
            gotoxy(curPos.X + (x * 2), curPos.Y + y);

            if (blockinfo[y][x])
                printf("  ");
        }
    }
    gotoxy(curPos.X, curPos.Y);
}