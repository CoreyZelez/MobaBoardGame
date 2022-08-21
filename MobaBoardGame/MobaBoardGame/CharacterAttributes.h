#pragma once
struct CharacterAttributes
{
public:
	unsigned int points;  // Spent in order to move or attack.
	unsigned int movementCost;
	unsigned int attackCost;

	unsigned int health;
	unsigned int damage;

	unsigned int armour;
	unsigned int magicResist;
	unsigned int armourPenetration;
	unsigned int magicPenetration;
};

