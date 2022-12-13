#include "GameSquare.h"
#include <assert.h>
#include "Position.h"

GameSquare::GameSquare(Position position, SquareType type,  bool occupiable)
	: position(position), type(type), occupiable(occupiable)
{
	initSquare();
}

void GameSquare::draw(sf::RenderWindow &window) const
{
	window.draw(square);
}

const sf::RectangleShape & GameSquare::getRect() const
{
	return square;
}

Position GameSquare::getPosition() const
{
	return position;
}

SquareType GameSquare::getType() const
{
	return type;
}

void GameSquare::mark(sf::Color color)
{
	square.setFillColor(color);
	square.setOutlineColor(color);
	marked = true;
}

void GameSquare::unmark()
{
	square.setFillColor(fillColor);
	square.setOutlineColor(outlineColor);
	marked = false;
}

const GameEntity * GameSquare::getOccupant() const
{
	return occupant;
}

void GameSquare::setOccupant(GameEntity *occupant)
{
	assert(isVacant());
	this->occupant = occupant;
}

GameEntity * GameSquare::removeOccupant()
{
	GameEntity *currEntity = occupant;
	occupant = nullptr;
	return currEntity;
}

bool GameSquare::isVacant() const
{
	return (occupiable && occupant == nullptr);
}


void GameSquare::initSquare()
{
	square.setSize(sf::Vector2f(GRID_SQUARE_SIZE, GRID_SQUARE_SIZE));
	square.setOutlineThickness(GRID_OUTLINE_THICKNESS);
	const int x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x;
	const int y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y;
	square.setPosition(sf::Vector2f(x, y));
	colorSquare();
}

void GameSquare::colorSquare()
{
	switch(type)
	{
	case impassableForest:
		impassableForestColor();
		break;
	case deepWater:
		deepWaterColor();
		break;
	case mountain:
		mountainColor();
		break;
	case grass:
		grassColor();
		break;
	case mountainFloor:
		mountainFloorColor();
		break;
	case lava:
		lavaColor();
		break;
	}
}

void GameSquare::impassableForestColor()
{
	int red = 5;
	int green = 22;
	int blue = 0;
	int r = (rand() % 11);
	red += r;
	r = (rand() % 11);
	green += r;
	r = (rand() % 11);
	blue += r;
	fillColor = sf::Color(red, green, blue);

	red -= 10;
	green -= 10;
	blue -= 10;
	if(red < 0)
	{
		red = 0;
	}
	if(green < 0)
	{
		green = 0;
	}
	if(blue < 0)
	{
		blue = 0;
	}
	sf::Color outlineColor(red, green, blue);

	square.setFillColor(fillColor);
	square.setOutlineColor(outlineColor);
}

void GameSquare::deepWaterColor()
{
	int red = 5;
	int green = 12;
	int blue = 60;
	int r = (rand() % 3);
	green += r;
	r = (rand() % 3);
	blue += r;
	fillColor = sf::Color(red, green, blue);

	red -= 10;
	green -= 10;
	blue -= 10;
	if(red < 0)
	{
		red = 0;
	}
	if(green < 0)
	{
		green = 0;
	}
	if(blue < 0)
	{
		blue = 0;
	}
	sf::Color outlineColor(red, green, blue);

	square.setFillColor(fillColor);
	square.setOutlineColor(outlineColor);
}

void GameSquare::mountainColor()
{
	int red = 15;
	int green = 15;
	int blue = 15;
	int r = (rand() % 2);
	red += r;
	r = (rand() % 2);
	green += r;
	r = (rand() % 2);
	blue += r;
	fillColor = sf::Color(red, green, blue);

	red -= 10;
	green -= 10;
	blue -= 10;
	if(red < 0)
	{
		red = 0;
	}
	if(green < 0)
	{
		green = 0;
	}
	if(blue < 0)
	{
		blue = 0;
	}
	outlineColor = sf::Color(red, green, blue);

	square.setFillColor(fillColor);
	square.setOutlineColor(outlineColor);
}

void GameSquare::grassColor()
{
	int red = 2;
	int green = 40;
	int blue = 2;
	int r = (rand() % 2);
	red += r;
	r = (rand() % 6);
	green += r;
	r = (rand() % 2);
	blue += r;
	fillColor = sf::Color(red, green, blue);

	red -= 10;
	green -= 10;
	blue -= 10;
	if(red < 0)
	{
		red = 0;
	}
	if(green < 0)
	{
		green = 0;
	}
	if(blue < 0)
	{
		blue = 0;
	}
	outlineColor = sf::Color(red, green, blue);

	square.setFillColor(fillColor);
	square.setOutlineColor(outlineColor);
}

void GameSquare::lavaColor()
{
	int red = 100;
	int green = 30;
	int blue = 5;
	int r = (rand() % 3);
	red += r;
	r = (rand() % 10);
	green += r;
	r = (rand() % 3);
	blue += r;
	fillColor = sf::Color(red, green, blue);

	red -= 10;
	green -= 10;
	blue -= 10;
	if(red < 0)
	{
		red = 0;
	}
	if(green < 0)
	{
		green = 0;
	}
	if(blue < 0)
	{
		blue = 0;
	}
	outlineColor = sf::Color(red, green, blue);

	square.setFillColor(fillColor);
	square.setOutlineColor(outlineColor);
}

void GameSquare::mountainFloorColor()
{
	int red = 24;
	int green = 24;
	int blue = 24;
	int r = (rand() % 3);
	red += r;
	r = (rand() % 3);
	green += r;
	r = (rand() % 3);
	blue += r;
	fillColor = sf::Color(red, green, blue);

	red -= 10;
	green -= 10;
	blue -= 10;
	if(red < 0)
	{
		red = 0;
	}
	if(green < 0)
	{
		green = 0;
	}
	if(blue < 0)
	{
		blue = 0;
	}
	outlineColor = sf::Color(red, green, blue);

	square.setFillColor(fillColor);
	square.setOutlineColor(outlineColor);
}

void GameSquare::shallowWaterColor()
{
	int red = 5;
	int green = 12;
	int blue = 90;
	int r = (rand() % 3);
	green += r;
	r = (rand() % 3);
	blue += r;
	fillColor = sf::Color(red, green, blue);

	red -= 10;
	green -= 10;
	blue -= 10;
	if(red < 0)
	{
		red = 0;
	}
	if(green < 0)
	{
		green = 0;
	}
	if(blue < 0)
	{
		blue = 0;
	}
	outlineColor = sf::Color(red, green, blue);

	square.setFillColor(fillColor);
	square.setOutlineColor(outlineColor);
}

