#include "GameHandler.h"
#include <iostream>

GameHandler::GameHandler(Game &game)
	: game(game)
{
}

void GameHandler::handleInput(sf::RenderWindow & window)
{
	if(game.characterIsSelected())
	{
		if(!rightLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
			// Attempt to move character to square at coords. Unselects character if unsuccesful.
			game.moveSelectedCharacter(worldPos.x, worldPos.y); 
		}

		rightLock = true;
	}
	// Entity Selection
	else if(!rightLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))  // May have to do on click not press.
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		game.selectCharacter(worldPos.x, worldPos.y);  // Game attempts to select character at coords.

		rightLock = true;
	}

	// Unlock mouse;
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		rightLock = false;
	}
}
