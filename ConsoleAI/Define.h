#pragma once

using std::cout;
using std::endl;

enum MapSize
{
	MapX = 20,
	MapY = 40,
};

enum class UpdateState
{
	Run,
	Final,
};

enum class KeySet
{
	None = 0,

	Left,
	Up,
	Right,
	Down,
};

void GotoXY(int x, int y);



#define SAFE_DELETE(x)		{if ((x) != nullptr) {delete (x); (x) = nullptr;}}
#define SAFE_DELETE_ARR(x)	{if ((x) != nullptr) {delete[] (x); (x) = nullptr;}}