#pragma once
#include "SFML/Graphics.hpp"
#include "Team.h"

class Position;

class ActiveEntityImage
{
public:
	ActiveEntityImage(Position position, Team team, sf::Color left, sf::Color right);
	ActiveEntityImage(Position position, Team team);

	void updatePosition(Position position);
	void updateHealthBar(); // In future include shield.

	void setHealth(const int &currHealth, int maxHealth);

	bool isAt(float x, float y) const;  // Returns true if supplied coordinates lie inside backSquare.

	void draw(sf::RenderWindow &window);

private:
	void initBackColor(Team team);

	sf::RectangleShape leftSquare;
	sf::RectangleShape rightSquare;
	sf::RectangleShape backSquare;

	sf::RectangleShape healthBarFront;
	sf::RectangleShape healthBarBack;

	const int *currHealth = nullptr;
	int maxHealth;

};

