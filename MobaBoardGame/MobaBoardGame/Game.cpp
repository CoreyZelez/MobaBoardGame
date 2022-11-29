#include "Game.h"
#include "CharacterFactory.h"
#include <iostream>

Game::Game()
{
	CharacterFactory factory;
	// Blue team.
	std::shared_ptr<Character> character1 = factory.createVoidArcherLeanna({ 8, 14 }, 1);
	character1.get()->initTeam(blue);

	// Red team.
	std::shared_ptr<Character> character2 = std::shared_ptr<Character>(factory.createBloodlordKlaus({ 1, 1 }, 1));
	character2.get()->initTeam(red);

	// Place characters on board.
	board.initEntity(character1.get());  
	board.initEntity(character2.get());

	characters.push_back(character1);
	characters.push_back(character2);
}

void Game::update()
{
	// board.update();  Important that board is updated before other entities.

	for(const auto &character : characters)
	{
		character.get()->update();
	}
}

void Game::draw(sf::RenderWindow &window)
{
	board.draw(window);

	for(const auto &character : characters)
	{
		character.get()->draw(window);
	}
}

void Game::moveSelectedCharacter(float x, float y)
{
	assert(selectedCharacterNum != -1);  // There must be a selected character.

	Character *character = characters[selectedCharacterNum].get();
	Position characterPosition = character->getPosition();

	GameSquare *sourceSquare = board.getSquare(characterPosition);
	GameSquare *targetSquare = board.getSquare(x, y);

	if(sourceSquare == targetSquare)
	{
		return;
	}

	assert(sourceSquare->getOccupant() == character);  // Character position consistent with board.

	Position target = targetSquare->getPosition();

	assert(target == board.globalCoordsToPosition(x, y));  // Sanity check.

	if(targetSquare->isVacant())
	{
		// int cost = somefunction(...)
		int cost = -1;  // temp
		if(character->move(target, cost))
		{
			board.moveEntity(characterPosition, target);

			assert(board.getSquare(target)->getOccupant() == character);
			assert(sourceSquare->isVacant());
		}
	}

	unselectCharacter();
}

void Game::unselectCharacter()
{
	board.resetMarkedSquares();
	selectedCharacterNum = -1;
}


void Game::selectCharacter(float x, float y)
{
	for(int charNum = 0; charNum < characters.size(); ++charNum)
	{
		if(characters[charNum].get()->isAt(x, y))
		{
			selectedCharacterNum = charNum;
			Character &character = *characters[charNum].get();

			const int movementPoints = character.getMovementPoints();
			const int actionPoints = character.getActionPoints();
			if(actionPoints > movementPoints)
			{
				board.markSquares(character.getPosition(), movementPoints);
			}
			else
			{
				board.markSquares(character.getPosition(), actionPoints);
			}

			return;
		}
	}

	selectedCharacterNum = -1;
}

bool Game::characterIsSelected() const
{
	return selectedCharacterNum != -1;
}

void Game::resetSelections()
{
	selectedCharacterNum = -1;
}
