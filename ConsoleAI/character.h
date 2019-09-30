#pragma once
class Character
{
public:
	Character() {}
	Character(int x, int y, std::string ch) : CharX(x), CharY(y), Charac(ch)
	{
		CharX = 0;
		CharY = 0;
		Charac = "  ";
	}
	~Character() {}

	virtual void CharacterPrint() { }

private:

	std::string Charac;

	int CharX;
	int CharY;
};

