#pragma once
#include "MainGame.h"

class GameFPS
{
public:
	GameFPS();
	~GameFPS();

	void Run();
	constexpr static float GetTargetFPS();

protected:

	UpdateState Update(float DeltaTime);

private:

	MainGame Mg;

	long DeltaTick;
	long LastStamp = 0;
};

