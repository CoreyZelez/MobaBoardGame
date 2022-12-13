#include "Game.h"
#include "CharacterFactory.h"
#include "MapSaveHandler.h"
#include <iostream>

Game::Game()
{
	// Init board.
	MapSaveHandler saveHandler;
	gameBoard = saveHandler.readBoardFile("map V1.1");
	gameBoard.get()->initBlueSpawn({ 50, 12 });
	gameBoard.get()->initRedSpawn({ 51, 13 });

	CharacterFactory factory;

	// Blue team.
	std::shared_ptr<Character> character1 = factory.createVoidArcherLeanna(*gameBoard.get(), blue, 1);
	character1.get()->init();

	// Red team.
	std::shared_ptr<Character> character2 = std::shared_ptr<Character>(factory.createBloodlordKlaus(*gameBoard.get(), red, 1));
	character2.get()->init();           

	characters.push_back(character1);
	characters.push_back(character2);
}

void Game::update()
{
	// board.update();

	if(!endTurn)
	{
		return;
	}

	for(const auto &character : characters)
	{
		character.get()->update();
	}

	switchCurrTeam();
	resetSelections();

	endTurn = false;
}

void Game::draw(sf::RenderWindow &window)
{
	gameBoard.get()->draw(window);

	for(const auto &character : characters)
	{
		character.get()->draw(window);
	}
}

bool Game::moveSelectedCharacter(float x, float y)
{
	if(selectedCharacterNum == -1)
	{
		return false;
	}
	assert(selectedCharacterNum != -1);  // There must be a selected character.

	Character &character = *characters[selectedCharacterNum].get();

	assert(character.getTeam() == currTeam);

	Position characterPosition = character.getPosition();

	GameSquare *sourceSquare = gameBoard.get()->getSquare(characterPosition);
	GameSquare *targetSquare = gameBoard.get()->getSquare(x, y);

	if(sourceSquare == targetSquare)
	{
		return false;
	}

	assert(sourceSquare->getOccupant() == &character);  // Character position consistent with board.

	Position target = targetSquare->getPosition();

	assert(target == gameBoard.get()->globalCoordsToPosition(x, y));  // Sanity check.

	if(targetSquare->isVacant())
	{
		std::list<Node> markedNodes = gameBoard.get()->getMarkedNodes();
		auto it = std::find_if(markedNodes.begin(), markedNodes.end(), [target](Node node)
		{ return node.position == target; });

		if(it != markedNodes.end())
		{
			int cost = it->value;
			assert(character.move(target, cost));  // Move character. Must be successful.

			gameBoard.get()->moveEntity(characterPosition, target);

			assert(gameBoard.get()->getSquare(target)->getOccupant() == &character);
			assert(sourceSquare->isVacant());

			return true;
		}
	}

	return false;
}

void Game::unselectCharacter()
{
	gameBoard.get()->resetMarkedSquares();
	selectedCharacterNum = -1;
}

void Game::switchCurrTeam()
{
	if(currTeam == blue)
	{
		currTeam = red;
	}
	else
	{
		currTeam = blue;
	}
}

void Game::setTurnEnd()
{
	endTurn = true;
	setState(nothingSelected);
}

void Game::selectCharacter(float x, float y)
{
	for(int charNum = 0; charNum < characters.size(); ++charNum)
	{
		if(characters[charNum].get()->isAt(x, y))
		{
			selectedCharacterNum = charNum;
			Character &character = *characters[charNum].get();

			if(character.getTeam() != currTeam)
			{
				selectedCharacterNum = -1;
				return;
			}
			setState(move);

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
	unselectCharacter();
}

void Game::markSquares(GameState state)
{
	assert(characterIsSelected());

	gameBoard.get()->resetMarkedSquares();

	assert(selectedCharacterNum != -1);
	Character &character = *characters[selectedCharacterNum].get();
	assert(character.getTeam() == currTeam);

	const int movementPoints = character.getAttributes().actionAttributes.movementPoints;
	const int actionPoints = character.getAttributes().actionAttributes.points;
	const int attackPoints = character.getAttributes().actionAttributes.attackPoints;
	const int range = character.getAttributes().actionAttributes.range;
	const int ability1Range = character.getAbility1Range();
	const int ability2Range = character.getAbility2Range();
	const Position position = character.getPosition();

	switch(state)
	{
	case move:
		if(actionPoints > movementPoints)
		{
			gameBoard.get()->markSquares(character.getPosition(), movementPoints, true, false, sf::Color::Yellow);
		}
		else
		{
			gameBoard.get()->markSquares(character.getPosition(), actionPoints, true, false, sf::Color::Yellow);
		}
		break;

	case basicAttack:
		// Determines color. Grey if not enough action points.
		if(character.unableToBasicAttack())
		{
			sf::Color color = sf::Color(40, 40, 40);
			gameBoard.get()->markSquares(position, range, false, true, color);
			break;
		}

		gameBoard.get()->markSquares(position, range, false, true, sf::Color::Magenta);
		break;

	case ability1:
		// Color squares grey if not enough action points.
		if(character.unableToUseAbility1())
		{
			sf::Color color = sf::Color(40, 40, 40);
			gameBoard.get()->markSquares(position, ability1Range, false, true, color);
			break;
		}

		gameBoard.get()->markSquares(position, ability1Range, false, true, sf::Color(255, 0, 120));
		break;

	case ability2:
		// Color squares grey if not enough action points.
		if(character.unableToUseAbility2())
		{
			sf::Color color = sf::Color(40, 40, 40);
			gameBoard.get()->markSquares(position, ability2Range, false, true, color);
			break;
		}

		gameBoard.get()->markSquares(position, ability2Range, false, true, sf::Color(255, 0, 120));
		break;
	}
}

void Game::setState(GameState nextState)
{
	switch(currState)
	{
	case nothingSelected:
		switch(nextState)
		{
		case move:
			markSquares(move); 
		}

	case move:
		switch(nextState)
		{
		case nothingSelected:
			resetSelections();
			break;
		case move:
			gameBoard.get()->resetMarkedSquares();
			markSquares(move);
			break;
		case basicAttack:
			gameBoard.get()->resetMarkedSquares();
			markSquares(basicAttack);
			break;
		case ability1:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability1);
			break;
		case ability2:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability2);
			break;
		}
		break;

	case basicAttack:
		switch(nextState)
		{
		case move:
			gameBoard.get()->resetMarkedSquares();
			markSquares(move);
			break;
		case ability1:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability1);
			break;
		case ability2:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability2);
			break;
		case nothingSelected:
			resetSelections();
			break;
		}

	case ability1:
		switch(nextState)
		{
		case move:
			gameBoard.get()->resetMarkedSquares();
			markSquares(move);
			break;
		case basicAttack:
			gameBoard.get()->resetMarkedSquares();
			markSquares(basicAttack);
			break;
		case nothingSelected:
			resetSelections();
			break;
		case ability2:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability2);
			break;
		}

	case ability2:
		switch(nextState)
		{
		case move:
			gameBoard.get()->resetMarkedSquares();
			markSquares(move);
			break;
		case basicAttack:
			gameBoard.get()->resetMarkedSquares();
			markSquares(basicAttack);
			break;
		case nothingSelected:
			resetSelections();
			break;
		case ability1:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability1);
			break;
		}
		break;
	}

	currState = nextState;
}

GameState Game::getState()
{
	return currState;
}

bool Game::selectedCharacterDoAttack(float x, float y)
{
	for(int charNum = 0; charNum < characters.size(); ++charNum)
	{
		if(characters[charNum].get()->isAt(x, y))
		{
			Character &character = *characters[selectedCharacterNum].get();
			Character &target = *characters[charNum].get();

			assert(currTeam == character.getTeam());

			if(target.getTeam() == currTeam)
			{
				return false;
			}

			return character.basicAttack(target);
		}
	}
}

bool Game::selectedCharacterUseAbility1(float x, float y)
{
	for(int charNum = 0; charNum < characters.size(); ++charNum)
	{
		if(characters[charNum].get()->isAt(x, y))
		{
			Character &character = *characters[selectedCharacterNum].get();
			Character &target = *characters[charNum].get();

			assert(currTeam == character.getTeam());

			return character.useAbility1(target);  // True indicates valid target and ability gets used.
		}
	}

	return false;  
}

bool Game::selectedCharacterUseAbility2(float x, float y)
{
	for(int charNum = 0; charNum < characters.size(); ++charNum)
	{
		if(characters[charNum].get()->isAt(x, y))
		{
			Character &character = *characters[selectedCharacterNum].get();
			Character &target = *characters[charNum].get();

			assert(currTeam == character.getTeam());

			return character.useAbility2(target);  // True indicates valid target and ability gets used.
		}
	}

	return false;
}


