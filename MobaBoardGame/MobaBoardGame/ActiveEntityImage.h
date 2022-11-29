#pragma once
#include "SFML/Graphics.hpp"
#include "Team.h"

class Position;

class ActiveEntityImage
{
public:
	ActiveEntityImage(Position position);
	void initBackColor(Team team);
	void initLeftColor(sf::Color left);
	void initRightColor(sf::Color right);

	void updatePosition(Position position);

	bool isAt(float x, float y) const;  // Returns true if supplied coordinates lie inside backSquare.

	void draw(sf::RenderWindow &window);

private:
	sf::RectangleShape leftSquare;
	sf::RectangleShape rightSquare;
	sf::RectangleShape backSquare;
};

