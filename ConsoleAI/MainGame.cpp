#include "pch.h"
#include "MainGame.h"
#include "Monster.h"

void MainGame::Update(float DeltaTime)
{
	NowTime += DeltaTime;

	if (NowTime > SetTime)
	{
		KeyChack();

		Render();

		NowTime -= SetTime;
	}
}

void MainGame::Render()
{
	Monster MSter(CharacterX, CharacterY, "бс");

	MSter.CharacterPrint();

	MainGame::Release(CharacterX, CharacterY);
}

void MainGame::PlayerSerch()
{

}

void MainGame::Release(int x, int y)
{
	GotoXY(x, y);
	cout << "  ";
}

void MainGame::KeyChack()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		KeyInput(KeySet::Left);
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		KeyInput(KeySet::Right);
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		KeyInput(KeySet::Up);
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		KeyInput(KeySet::Down);
	}
}

void MainGame::KeyInput(KeySet EKey)
{
	switch (EKey)
	{
	case KeySet::Left: --CharacterX;
		break;
	case KeySet::Up: --CharacterY;
		break;
	case KeySet::Right: ++CharacterX;
		break;
	case KeySet::Down: ++CharacterY;
		break;
	default: break;
	}
}