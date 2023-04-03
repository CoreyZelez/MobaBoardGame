#pragma once
#include <vector>
#include "GameBoard.h"
#include "Character.h"
#include "Minion.h"
#include "MinionSpawner.h"

enum GameState
{
	moveState,  // Occurrs initially upon character selection.
	basicAttackState,
	ability1State,
	ability2State,
	buyMenuState,
	nothingSelectedState
};

class Game
{
public:
	Game();  // Predefined game.

	void update();
	void draw(sf::RenderWindow &window);

	void setTurnEnd();
	GameBoard& getBoard();
	Character* getCharacterAt(Position position);
	Minion* getMinionAt(Position position);

	// Entity Removal.
	void remove(Minion &minion);

	// Selection
	bool selectCharacter(float x, float y);
	bool characterIsSelected() const;
	void resetSelections();
	void markSquares(GameState state);  // May be able to remove parameters.

	// Game state.
	void setState(GameState state);
	GameState getState();

	// Entity actions
	bool selectedCharacterDoAttack(float x, float y);  // True represents successful (i.e in range) attack on an entity.
	bool selectedCharacterUseAbility(int abilityNum, float x, float y);
	bool moveSelectedCharacter(float x, float y);

private:
	// Functions
	void removeDeadMinions();
	void updateMinions();

	void unselectCharacter();
	void switchCurrTeam();

	int selectedCharacterNum = -1;  // Represents position in getCharacter array. -1 indicates no character selected.

	std::unique_ptr<GameBoard> gameBoard;

	std::vector<std::shared_ptr<Character>> characters;

	std::vector<MinionSpawner> minionSpawners;
	std::vector<std::shared_ptr<Minion>> minions;

	Team currTeam = blue;  // team that can move.
	bool endTurn = false;
	GameState currState = nothingSelectedState;
};

