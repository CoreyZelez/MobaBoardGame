#pragma once
#include <vector>
#include "GameBoard.h"
#include "Character.h"

class Game
{
public:
	Game();

private:
	GameBoard board;
	std::vector<Character> characters;
};

