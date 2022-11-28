#include "GameSquare.h"
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

void GameSquare::initSquare()
{
	square.setSize(sf::Vector2f(squareSize, squareSize));
	square.setOutlineThickness(outlineThickness);
	const int x = (100 + outlineThickness) * position.x;
	const int y = (100 + outlineThickness) * position.y;
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
	}
}

void GameSquare::impassableForestColor()
{
	int red = 10;
	int green = 30;
	int blue = 5;
	int r = (rand() % 11) - 5;
	red += r;
	r = (rand() % 11) - 5;
	green += r;
	r = (rand() % 11) - 5;
	blue += r;
	sf::Color fillColor(red, green, blue);

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
	sf::Color fillColor(red, green, blue);

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
