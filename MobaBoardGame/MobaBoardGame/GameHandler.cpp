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
	case nothingSelectedState:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			game.selectCharacter(worldPos.x, worldPos.y);  // Game attempts to select character at coords.
		}
		break;
	case moveState:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			bool successfulCharacterMove = game.moveSelectedCharacter(worldPos.x, worldPos.y);

			if(successfulCharacterMove == true)
			{
				game.setState(moveState);
			}
			else if(game.selectCharacter(worldPos.x, worldPos.y))  // Attempts to change selection to character of same team.
			{
				break;
			}
			else
			{
				game.setState(nothingSelectedState);
			}
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputLock = true;
			game.setState(basicAttackState);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			inputLock = true;
			game.setState(ability1State);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputLock = true;
			game.setState(ability2State);
		}
		break;

	case basicAttackState:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			bool successfulAttack = game.selectedCharacterDoAttack(worldPos.x, worldPos.y);

			if(successfulAttack == true)
			{
				game.setState(moveState);
			}
			else
			{
				game.setState(nothingSelectedState);
			}
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputLock = true;
			game.setState(moveState);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			inputLock = true;
			game.setState(ability1State);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputLock = true;
			game.setState(ability2State);
		}
		break;
	case ability1State:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			bool successfulAbilityUse = game.selectedCharacterUseAbility(1, worldPos.x, worldPos.y);
			if(successfulAbilityUse == true)
			{
				game.setState(moveState);
			}
			else
			{
				game.setState(nothingSelectedState);
			}
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputLock = true;
			game.setState(basicAttackState);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			inputLock = true;
			game.setState(moveState);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputLock = true;
			game.setState(ability2State);
		}
		break;
	case ability2State:
		if(!inputLock && sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			inputLock = true;

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			bool successfulAbilityUse = game.selectedCharacterUseAbility(2, worldPos.x, worldPos.y);
			if(successfulAbilityUse == true)
			{
				game.setState(moveState);
			}
			else
			{
				game.setState(nothingSelectedState);
			}
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inputLock = true;
			game.setState(basicAttackState);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			inputLock = true;
			game.setState(ability1State);
		}
		else if(!inputLock && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			inputLock = true;
			game.setState(moveState);
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

