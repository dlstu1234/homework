#include "pch.h"
#include "GameFPS.h"
#include "MainGame.h"

GameFPS::GameFPS()
{
}

GameFPS::~GameFPS()
{
}

constexpr float GameFPS::GetTargetFPS()
{
	constexpr float TargetFPS = 60;
	return (1 / TargetFPS) * 1000;
}

void GameFPS::Run()
{
	system(" mode  con lines=50   cols=80 ");

	while (true)
	{
		clock_t Now = clock();
		clock_t Term = Now - LastStamp;

		if (Term > GetTargetFPS())
		{
			DeltaTick = Term;
			LastStamp = Now;

			float FDeltaTime = DeltaTick / (float)1000;

			if (Update(FDeltaTime) == UpdateState::Final) { break; }

		}
	}
}

UpdateState GameFPS::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		return UpdateState::Final;
	}

	Mg.Update(DeltaTime);

	return UpdateState::Run;
}


