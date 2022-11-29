#pragma once
#include <vector>
#include "GameBoard.h"
#include <vector>
#include "Character.h"

class Game
{
public:
	Game();  // Predefined game.

	void update();
	void draw(sf::RenderWindow &window);

	// Selection
	void selectCharacter(float x, float y);
	bool characterIsSelected() const;
	void resetSelections();

	// Entity actions
	void moveSelectedCharacter(float x, float y);

private:
	// Functions
	void unselectCharacter();

	int selectedCharacterNum = -1;  // Represents position in getCharacter array. -1 indicates no character selected.

	GameBoard board;
	std::vector<std::shared_ptr<Character>> characters;
};

