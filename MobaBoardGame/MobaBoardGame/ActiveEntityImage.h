#pragma once
#include "SFML/Graphics.hpp"
#include "Team.h"
#include "Position.h"

class ActiveEntityImage
{
public:
	ActiveEntityImage(Team team, sf::Color left, sf::Color right);  // For characters.
	ActiveEntityImage(Team team, bool isMinion);  // For minions.
	ActiveEntityImage();  // For neutrals.

	void updatePosition(Position position);
	void updateHealthBar(); // In future include shield.

	void setHealth(const int &currHealth, const int maxHealth);

	bool isAt(float x, float y) const;  // Returns true if supplied coordinates lie inside backSquare.

	void draw(sf::RenderWindow &window);

private:
	void initBackColor(Team team);

	sf::RectangleShape leftSquare;
	sf::RectangleShape rightSquare;
	sf::RectangleShape backSquare;

	sf::RectangleShape healthBarFront;
	sf::RectangleShape healthBarBack;

	bool isMinion = false;  // minions healthbar is unique.
	const int *currHealth = nullptr;
	int maxHealth;
};

