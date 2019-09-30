#include "pch.h"
#include "Define.h"

void GotoXY(int x, int y)
{
	COORD Pos = { (short)x, (short)y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}