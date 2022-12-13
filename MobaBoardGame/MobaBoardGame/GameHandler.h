#pragma once
#include "Game.h"

class GameHandler
{
public:
	GameHandler(Game &game);

	void handleInput(sf::RenderWindow &window);

private:
	bool timeBetweenInputValid();

	bool inputLock = false;

	Game &game;

	const float minSecondsBetweenInput = 0.05f;
	sf::Clock inputClock;
};

