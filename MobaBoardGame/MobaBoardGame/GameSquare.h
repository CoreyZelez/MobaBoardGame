#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"
#include "SquareType.h"

static const float squareSize = 100;
static const float outlineThickness = 5;

class GameSquare
{
public:
	GameSquare(Position position, SquareType type, bool occupiable);

	void draw(sf::RenderWindow &window) const;

	const sf::RectangleShape &getRect() const;
	Position getPosition() const;

	SquareType getType() const;

protected:
	void initSquare();

private:
	void colorSquare();
	void impassableForestColor();  // Colors square based for impassable forest.
	void deepWaterColor();  // Colors square based for impassable forest.


	SquareType type;
	sf::RectangleShape square;
	sf::Color fillColor;
	sf::Color outlineColor;

	Position position;

	bool occupiable = true;
};


