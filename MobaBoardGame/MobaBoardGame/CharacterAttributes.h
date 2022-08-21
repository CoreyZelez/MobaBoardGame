#pragma once


struct BasicAttributes
{
public: 
	unsigned int health;
	unsigned int healthRegen;
	unsigned int magicPower;
	unsigned int damage;
};

struct ActionAttributes
{
	// NOTE: can only use 1 ability per turn.
	unsigned int points;  // Spent in order to move or attack or use ability.
	unsigned int movementPoints;  // Spent in order to move.
	unsigned int attackPoints;  // Spent in order to attack.
	unsigned int movementCost;
	unsigned int attackCost;
};

struct ProtectionAttributes
{
	unsigned int armour;
	unsigned int magicResist;
	unsigned int armourPenetration;
	unsigned int magicPenetration;
};

struct CharacterAttributes
{
public:
	BasicAttributes basicAttributes;
	ActionAttributes actionAttributes;
	ProtectionAttributes protectionAttributes;
};

