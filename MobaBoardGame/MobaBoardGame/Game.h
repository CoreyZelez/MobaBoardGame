#pragma once
#include <vector>
#include "GameBoard.h"
#include <vector>
#include "Character.h"

enum GameState
{
	move,  // Occurrs initially upon character selection.
	basicAttack,
	ability1,
	ability2,
	buyMenu,
	nothingSelected
};

class Game
{
public:
	Game();  // Predefined game.

	void update();
	void draw(sf::RenderWindow &window);

	void setTurnEnd();

	// Selection
	void selectCharacter(float x, float y);
	bool characterIsSelected() const;
	void resetSelections();

	void markSquares(GameState state);  // May be able to remove parameters.

	void setState(GameState state);
	GameState getState();

	// Entity actions
	bool selectedCharacterDoAttack(float x, float y);  // True represents successful (i.e in range) attack on an entity.
	bool selectedCharacterUseAbility1(float x, float y);
	bool selectedCharacterUseAbility2(float x, float y);
	bool moveSelectedCharacter(float x, float y);

private:
	// Functions
	void unselectCharacter();
	void switchCurrTeam();

	int selectedCharacterNum = -1;  // Represents position in getCharacter array. -1 indicates no character selected.

	std::unique_ptr<GameBoard> gameBoard;
	std::vector<std::shared_ptr<Character>> characters;
	Team currTeam = blue;  // team that can move.
	bool endTurn = false;
	GameState currState = nothingSelected;
};

