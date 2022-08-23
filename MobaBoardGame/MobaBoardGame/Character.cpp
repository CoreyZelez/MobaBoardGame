#include "Character.h"
#include <iostream>

const std::array<int, 8> Character::experienceForLevel = { 0, 20, 45, 80, 130, 200, 300, 450 };

Character::Character(std::array<const CharacterAttributes, 8> baseAttributes)
	: baseAttributes(baseAttributes)
{
	currAttributes = baseAttributes[0];  // Current attributes starts at level 0 base attributes.
}

void Character::update()
{
}

void Character::basicAttack(Character &enemyCharacter)
{
}

void Character::printAttributes()
{
	std::cout << currAttributes.healthAttributes.health;
}

void Character::updateCurrAttributes()
{
	const int health = currAttributes.healthAttributes.health;  // Health is not recalculated.
	currAttributes = baseAttributes[levelInformation.level];
	currAttributes.healthAttributes.health = health;

	//for(auto &effect : healthAttributeDurationEffects)
	//{
		//effect.update(currAttributes.healthAttributes);
	//}
}



