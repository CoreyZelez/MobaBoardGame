#include "GameHandler.h"
#include <iostream>

GameHandler::GameHandler(Game &game)
	: game(game)
{
}

void GameHandler::handleInput(sf::RenderWindow & window)
{
	if(!timeBetweenInputValid())
	{
		return;
	}

	// Input clock resetting.
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		inputClock.restart();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		inputClock.restart();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		inputClock.restart();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		inputClock.restart();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		inputClock.restart();
	}


	GameState currState = game.getState();

	switch(currState)
	{
	case nothingSelected:	
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			game.selectCharacter(worldPos.x, worldPos.y);  // Game attempts to select character at coords.
		}
		break;
	case move:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			bool successfulCharacterMove = game.moveSelectedCharacter(worldPos.x, worldPos.y);
			if(successfulCharacterMove == true)
			{
				game.setState(move);
			}
			else
			{
				game.setState(nothingSelected);
			}
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputLock = true;
			game.setState(basicAttack);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			inputLock = true;
			game.setState(ability1);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputLock = true;
			game.setState(ability2);
		}
		break;

	case basicAttack:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			bool successfulAttack = game.selectedCharacterDoAttack(worldPos.x, worldPos.y);
			if(successfulAttack == true)
			{
				game.setState(move);
			}
			else
			{
				game.setState(nothingSelected);
			}
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputLock = true;
			game.setState(move);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			inputLock = true;
			game.setState(ability1);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputLock = true;
			game.setState(ability2);
		}
		break;
	case ability1:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			bool successfulAbilityUse = game.selectedCharacterUseAbility1(worldPos.x, worldPos.y);
			if(successfulAbilityUse == true)
			{
				game.setState(move);
			}
			else
			{
				game.setState(nothingSelected);
			}
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputLock = true;
			game.setState(basicAttack);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			inputLock = true;
			game.setState(move);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputLock = true;
			game.setState(ability2);
		}
		break;
	case ability2:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			bool successfulAbilityUse = game.selectedCharacterUseAbility2(worldPos.x, worldPos.y);
			if(successfulAbilityUse == true)
			{
				game.setState(move);
			}
			else
			{
				game.setState(nothingSelected);
			}
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputLock = true;
			game.setState(basicAttack);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			inputLock = true;
			game.setState(ability1);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputLock = true;
			game.setState(move);
		}
		break;
	}

	if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		inputLock = true;
		game.setTurnEnd();
	}

	if(!sf::Mouse::isButtonPressed(sf::Mouse::Right)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		inputLock = false;
	}
}

bool GameHandler::timeBetweenInputValid()
{
	if(inputClock.getElapsedTime().asSeconds() > minSecondsBetweenInput)
	{
		return true;
	}

	return false;
}

