#include "pch.h"
#include "Monster.h"

void Monster::CharacterPrint()
{
	GotoXY(MonsterX, MonsterY);
	cout << "  " + MSter;
}