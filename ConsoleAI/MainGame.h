#pragma once
#include "Monster.h"
class MainGame
{
public:

	MainGame() {}

	void Update(float DeltaTime);
	void PlayerSerch();

	void Render();
	void Release(int x, int y);

	void KeyChack();
	void KeyInput(KeySet EKey);

private:

	int CharacterX = 5;
	int CharacterY = 5;

	float NowTime = 0;
	float SetTime = 0.2f;
};


