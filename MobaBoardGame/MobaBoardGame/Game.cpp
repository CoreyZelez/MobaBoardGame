#include "Game.h"
#include "CharacterFactory.h"
#include "MapSaveHandler.h"
#include <iostream>
#include <algorithm>
#include <random>


Game::Game()
{
	// Init board.
	MapSaveHandler saveHandler;
	gameBoard = saveHandler.readBoardFile("3v3 1.0");
	gameBoard.get()->initBlueSpawn({ 32, 3 });
	gameBoard.get()->initRedSpawn({ 32, 52 });

	CharacterFactory factory;

	// Blue team.
	std::shared_ptr<Character> character1 = factory.createVoidArcherLeanna(*gameBoard.get(), blue);
	character1.get()->init();

	std::shared_ptr<Character> character2 = factory.createAdominusSentinelAdar(*gameBoard.get(), blue);
	character2.get()->init();

	// Red team.
	std::shared_ptr<Character> character4 = std::shared_ptr<Character>(factory.createBloodlordKlaus(*gameBoard.get(), red));
	character4.get()->init();           

	characters.push_back(character1);
	characters.push_back(character2);

	characters.push_back(character4);

	// Creates bot lane path.
	std::vector<Position> path1;
	for(int i = 0; i < 17; ++i)
	{
		path1.push_back({ 31, 3 + i });
	}
	for(int i = 0; i < 16; ++i)
	{
		path1.push_back({ 32, 20 + i });
	}
	for(int i = 0; i < 17; ++i)
	{
		path1.push_back({ 33, 36 + i });
	}


	// Creates reversal of path1.
	std::vector<Position> path1Reverse = path1;
	std::reverse(path1Reverse.begin(), path1Reverse.end());

	MinionSpawner minionSpawnerBlue1(*this, blue, path1);
	MinionSpawner minionSpawnerRed1(*this, red, path1Reverse);
	minionSpawners.push_back(minionSpawnerBlue1);
	minionSpawners.push_back(minionSpawnerRed1);
}

void Game::update()
{
	// board.update();

	if(!endTurn)
	{
		return;
	}

	for(auto &character : characters)
	{
		character.get()->update();
	}

	updateMinions();

	for(MinionSpawner &spawner : minionSpawners)  // Make spawner a template class.
	{
		if(spawner.canSpawn())
		{
			std::shared_ptr<Minion> minion = spawner.spawnMinion();
			minion.get()->initImageHealth();
			minions.push_back(minion);  // spawn minion can become spawn when class is templated.
		}

		spawner.update();
	}

	switchCurrTeam();
	resetSelections();
	endTurn = false;
}

void Game::draw(sf::RenderWindow &window)
{
	gameBoard.get()->draw(window);

	for(auto &character : characters)
	{
		character.get()->draw(window);
	}

	for(auto &minion : minions)
	{
		if(minion.get() == nullptr)
		{
			continue;
		}
		minion.get()->draw(window);
	}
}

bool Game::moveSelectedCharacter(float x, float y)
{
	if(selectedCharacterNum == -1)
	{
		return false;
	}

	Character &character = *characters[selectedCharacterNum].get();

	assert(character.getTeam() == currTeam);

	return character.move(x, y);
}

void Game::removeDeadMinions()
{
	auto minion = minions.begin();
	while(minion != minions.end())
	{
		if(minion->get() == nullptr)
		{
			minion = minions.erase(minion);
		}
		else
		{
			++minion;
		}
	}
}

void Game::updateMinions()
{
	for(auto &minion : minions)
	{
		// assert(minion.get() != nullptr);
		if(minion.get() != nullptr)
		{
			minion.get()->update();
		}
	}

	removeDeadMinions();
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
	setState(nothingSelectedState);
}

GameBoard & Game::getBoard()
{
	return *gameBoard.get();
}

Character * Game::getCharacterAt(Position position)
{
	for(auto &character : characters)
	{
		if(character.get()->isAt(position))
		{
			return character.get();
		}
	}

	return nullptr;
}

Minion* Game::getMinionAt(Position position)
{
	for(auto &minion : minions)
	{
		if(minion.get() == nullptr)  
		{
			continue;
		}
		else if(minion.get()->isAt(position))
		{
			return minion.get();
		}
	}

	return nullptr;
}

void Game::remove(Minion &minion)
{
	auto iter = minions.begin();
	while(iter != minions.end())
	{
		if(iter->get() == &minion)
		{
			GameSquare *square = gameBoard->getSquare(iter->get()->getPosition());
			square->removeOccupant();
			iter->reset();
			return;
		}
		++iter;
	}

	assert(false);  // Should never be called on non-existent minion.
}

bool Game::selectCharacter(float x, float y)
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
				return false;
			}
			setState(moveState);

			return true;
		}
	}

	selectedCharacterNum = -1;
	return false;
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
	const int ability1Range = character.getAbilityRange(1);
	const int ability2Range = character.getAbilityRange(2);
	const Position position = character.getPosition();

	switch(state)
	{
	case moveState:
		if(actionPoints > movementPoints)
		{
			gameBoard.get()->markSquares(character.getPosition(), movementPoints, true, false, sf::Color::Yellow);
		}
		else
		{
			gameBoard.get()->markSquares(character.getPosition(), actionPoints, true, false, sf::Color::Yellow);
		}
		break;

	case basicAttackState:
		// Determines color. Grey if not enough action points.
		if(character.unableToBasicAttack())
		{
			sf::Color color = sf::Color(40, 40, 40);
			gameBoard.get()->markSquares(position, range, false, true, color);
			break;
		}

		gameBoard.get()->markSquares(position, range, false, true, sf::Color::Magenta);
		break;

	case ability1State:
		// Color squares grey if not enough action points.
		if(character.unableToUseAbility(1))
		{
			sf::Color color = sf::Color(40, 40, 40);
			gameBoard.get()->markSquares(position, ability1Range, false, true, color);
			break;
		}

		gameBoard.get()->markSquares(position, ability1Range, false, true, sf::Color(255, 0, 120));
		break;

	case ability2State:
		// Color squares grey if not enough action points.
		if(character.unableToUseAbility(2))
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
	case nothingSelectedState:
		switch(nextState)
		{
		case moveState:
			markSquares(moveState);
		}

	case moveState:
		switch(nextState)
		{
		case nothingSelectedState:
			resetSelections();
			break;
		case moveState:
			gameBoard.get()->resetMarkedSquares();
			markSquares(moveState);
			break;
		case basicAttackState:
			gameBoard.get()->resetMarkedSquares();
			markSquares(basicAttackState);
			break;
		case ability1State:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability1State);
			break;
		case ability2State:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability2State);
			break;
		}
		break;

	case basicAttackState:
		switch(nextState)
		{
		case moveState:
			gameBoard.get()->resetMarkedSquares();
			markSquares(moveState);
			break;
		case ability1State:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability1State);
			break;
		case ability2State:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability2State);
			break;
		case nothingSelectedState:
			resetSelections();
			break;
		}

	case ability1State:
		switch(nextState)
		{
		case moveState:
			gameBoard.get()->resetMarkedSquares();
			markSquares(moveState);
			break;
		case basicAttackState:
			gameBoard.get()->resetMarkedSquares();
			markSquares(basicAttackState);
			break;
		case nothingSelectedState:
			resetSelections();
			break;
		case ability2State:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability2State);
			break;
		}

	case ability2State:
		switch(nextState)
		{
		case moveState:
			gameBoard.get()->resetMarkedSquares();
			markSquares(moveState);
			break;
		case basicAttackState:
			gameBoard.get()->resetMarkedSquares();
			markSquares(basicAttackState);
			break;
		case nothingSelectedState:
			resetSelections();
			break;
		case ability1State:
			gameBoard.get()->resetMarkedSquares();
			markSquares(ability1State);
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
	Character &character = *characters[selectedCharacterNum].get();
	assert(currTeam == character.getTeam());

	// Handles attack on character.
	for(int charNum = 0; charNum < characters.size(); ++charNum)
	{
		if(characters[charNum].get()->isAt(x, y))
		{
			Character &target = *characters[charNum].get();

			if(target.getTeam() == currTeam)
			{
				return false;
			}

			return character.basicAttack(target);
		}
	}

	// Handles attack on minion.
	for(auto &minion : minions)
	{
		if(minion.get() == nullptr)  // Recall nullptr minions are awaiting removal.
		{
			continue;
		}
		if(minion.get()->isAt(x, y))
		{
			Minion &target = *minion.get();
			return character.basicAttack(target);
		}
	}
}

bool Game::selectedCharacterUseAbility(int abilityNum, float x, float y)
{
	for(int charNum = 0; charNum < characters.size(); ++charNum)
	{
		if(characters[charNum].get()->isAt(x, y))
		{
			Character &character = *characters[selectedCharacterNum].get();
			Character &target = *characters[charNum].get();

			assert(currTeam == character.getTeam());

			return character.useAbility(target, abilityNum);  // True indicates valid target and ability gets used.
		}
	}

	return false;
}


