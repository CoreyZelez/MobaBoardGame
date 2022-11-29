#pragma once
#include "Game.h"

class GameHandler
{
public:
	GameHandler(Game &game);

	void handleInput(sf::RenderWindow &window);

private:
	Game &game;
	bool rightLock = false;
};

