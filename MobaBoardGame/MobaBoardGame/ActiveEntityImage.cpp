#include "ActiveEntityImage.h"
#include "GameSquare.h"
#include "ActiveEntity.h"
#include <iostream>

const int SIZE_DECREMENT = 26;

ActiveEntityImage::ActiveEntityImage(Position position)
{
	const int halfDecrement = SIZE_DECREMENT / 2;
	const int size = GRID_SQUARE_SIZE - SIZE_DECREMENT;
	const int x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement;
	const int y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement;
	backSquare.setPosition(sf::Vector2f(x, y));
	backSquare.setSize(sf::Vector2f(size, size));
	backSquare.setOutlineThickness(GRID_OUTLINE_THICKNESS);

}

void ActiveEntityImage::initBackColor(Team team)
{
	sf::Color outlineColor(30, 30, 110);

	switch(team)
	{
	case blue:
	{
		sf::Color fillColor(20, 40, 190);  // Blue
		sf::Color outlineColor(210, 170, 0); // Yellow
		backSquare.setFillColor(fillColor);
		backSquare.setOutlineColor(outlineColor);
		break;
	}
	case red:

		break;
	case neutral:

		break;
	}
}

void ActiveEntityImage::initLeftColor(sf::Color left)
{
}

void ActiveEntityImage::initRightColor(sf::Color right)
{
}

void ActiveEntityImage::updatePosition(Position position)
{
	const int halfDecrement = SIZE_DECREMENT / 2;
	const int x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement;
	const int y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement;
	backSquare.setPosition(sf::Vector2f(x, y));
}

bool ActiveEntityImage::isAt(float x, float y) const
{
	return backSquare.getGlobalBounds().contains(x, y);
}

void ActiveEntityImage::draw(sf::RenderWindow &window)
{
	window.draw(backSquare);
}


