#include "ActiveEntityImage.h"
#include "GameSquare.h"
#include "GameEntity.h"
#include <iostream>

const int SIZE_DECREMENT = 26;
const int GAP = 4;
const int BAR_THICKNESS = 10;
const int BACK_SQUARE_SIZE = GRID_SQUARE_SIZE - SIZE_DECREMENT;
const int INNER_SQUARE_DIFF = 14;
const int INNER_SQUARE_WIDTH = (BACK_SQUARE_SIZE  / 2) - INNER_SQUARE_DIFF;
const int INNER_SQUARE_HEIGHT = BACK_SQUARE_SIZE - BAR_THICKNESS - INNER_SQUARE_DIFF;


ActiveEntityImage::ActiveEntityImage(Team team, sf::Color left, sf::Color right)
{
	const Position position = { 0, 0 };  // For initialisation.
	// Back square
	const int halfDecrement = SIZE_DECREMENT / 2;
	int x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement;
	int y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement;
	backSquare.setPosition(sf::Vector2f(x, y));
	backSquare.setSize(sf::Vector2f(BACK_SQUARE_SIZE, BACK_SQUARE_SIZE));
	backSquare.setOutlineThickness(GRID_OUTLINE_THICKNESS);
	initBackColor(team);

	// Healthbar
	y += BACK_SQUARE_SIZE - BAR_THICKNESS;
	healthBarBack.setPosition(sf::Vector2f(x, y));
	healthBarBack.setSize(sf::Vector2f(BACK_SQUARE_SIZE, BAR_THICKNESS));
	healthBarBack.setFillColor(sf::Color::Red);
	healthBarFront.setPosition(sf::Vector2f(x, y));
	healthBarFront.setFillColor(sf::Color::Green);
	healthBarFront.setSize(sf::Vector2f(0, BAR_THICKNESS));

	// Left square.
	x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement + INNER_SQUARE_DIFF;
	y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement + INNER_SQUARE_DIFF;
	leftSquare.setPosition(sf::Vector2f(x, y));
	leftSquare.setSize(sf::Vector2f(INNER_SQUARE_WIDTH, INNER_SQUARE_HEIGHT));
	leftSquare.setFillColor(left);

	// Right square
	x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement + INNER_SQUARE_DIFF + INNER_SQUARE_WIDTH;
	y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement;
	rightSquare.setPosition(sf::Vector2f(x, y));
	rightSquare.setSize(sf::Vector2f(INNER_SQUARE_WIDTH, INNER_SQUARE_HEIGHT));
	rightSquare.setFillColor(right);
}

ActiveEntityImage::ActiveEntityImage(Team team, bool isMinion)
	: isMinion(isMinion)
{
	const Position position = { 0, 0 };  // For initialisation.

	// Back square
	const int halfDecrement = SIZE_DECREMENT / 2;
	int x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement;
	int y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement;
	backSquare.setPosition(sf::Vector2f(x, y));
	backSquare.setSize(sf::Vector2f(BACK_SQUARE_SIZE, BACK_SQUARE_SIZE));
	backSquare.setOutlineThickness(GRID_OUTLINE_THICKNESS);
	initBackColor(team);

	// Healthbar
	y += BACK_SQUARE_SIZE - BAR_THICKNESS;
	healthBarBack.setPosition(sf::Vector2f(x, y));
	healthBarBack.setSize(sf::Vector2f(BACK_SQUARE_SIZE, BAR_THICKNESS));
	healthBarBack.setFillColor(sf::Color::Red);
	healthBarFront.setPosition(sf::Vector2f(x, y));
	healthBarFront.setFillColor(sf::Color::Green);
	healthBarFront.setSize(sf::Vector2f(0, BAR_THICKNESS));
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
	{
		sf::Color fillColor(190, 20, 40);  // red
		sf::Color outlineColor(210, 170, 0); // Yellow
		backSquare.setFillColor(fillColor);
		backSquare.setOutlineColor(outlineColor);
		break;
	}
	case neutral:

		break;
	}
}


void ActiveEntityImage::updatePosition(Position position)
{
	// Back square
	const int halfDecrement = SIZE_DECREMENT / 2;
	int x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement;
	int y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement;
	backSquare.setPosition(sf::Vector2f(x, y));

	// Healthbar
	y += BACK_SQUARE_SIZE - BAR_THICKNESS;
	healthBarBack.setPosition(sf::Vector2f(x, y));
	healthBarFront.setPosition(sf::Vector2f(x, y));

	// Left square
	x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement + INNER_SQUARE_DIFF;   
	y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement + INNER_SQUARE_DIFF;   
	leftSquare.setPosition(sf::Vector2f(x, y));

	// Right square
	x = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.x + halfDecrement + INNER_SQUARE_DIFF + INNER_SQUARE_WIDTH;
	y = (GRID_SQUARE_SIZE + GRID_OUTLINE_THICKNESS) * position.y + halfDecrement + INNER_SQUARE_DIFF;
	rightSquare.setPosition(sf::Vector2f(x, y));
}

void ActiveEntityImage::updateHealthBar()
{
	assert(currHealth != nullptr && *currHealth > 0);

	if(!isMinion)
	{
		double healthPercent = (double)*currHealth / (double)maxHealth;

		if(healthPercent > 1)
		{
			healthPercent = 1;
		}

		int length = (double)BACK_SQUARE_SIZE * healthPercent;

		healthBarFront.setSize(sf::Vector2f(length, BAR_THICKNESS));
	}
	else
	{
		const int reductionValue = 250;  // affects reduction of bar as currHealth reduces.
		double ratio = (double)*currHealth / (double)(reductionValue + *currHealth);

		assert(ratio > 0);

		int length = (double)BACK_SQUARE_SIZE * ratio;

		healthBarFront.setSize(sf::Vector2f(length, BAR_THICKNESS));
	}
}

void ActiveEntityImage::setHealth(const int &currHealth, const int maxHealth)
{
	this->currHealth = &currHealth;
	this->maxHealth = maxHealth;
}

bool ActiveEntityImage::isAt(float x, float y) const
{
	return backSquare.getGlobalBounds().contains(x, y);
}

void ActiveEntityImage::draw(sf::RenderWindow &window)
{
	window.draw(backSquare);
	window.draw(leftSquare);
	window.draw(rightSquare);

	if(currHealth != nullptr)
	{
		updateHealthBar();
		if(!isMinion)
		{
			window.draw(healthBarBack);
		}
		window.draw(healthBarFront);
	}
}


