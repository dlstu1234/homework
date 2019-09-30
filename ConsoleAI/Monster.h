#pragma once
#include "character.h"

class Monster : public Character
{
public:
	Monster() {}
	Monster(int x, int y, std::string ch) : Character(x, y, ch) 
	{
		MonsterX = x;
		MonsterY = y;
		MSter = ch;
	}

	virtual void CharacterPrint() override;

private:

	std::string MSter = "  ";

	int MonsterX = 0;
	int MonsterY = 0;
};

