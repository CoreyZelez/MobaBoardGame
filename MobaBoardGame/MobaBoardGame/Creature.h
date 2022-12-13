#pragma once
#include "GameEntity.h"

class Creature : public GameEntity
{
public:
	Creature(std::array<const EntityAttributes, 6> baseAttributes, sf::Color left, sf::Color right);

	virtual void attack(Character &target);

protected:
	void updateCurrAttributes();
	EntityAttributes getCurrAttributes();

private:
	// Attribute modifiers.
	// EffectsManager effects;

	// Core Attributes.
	const std::array<const EntityAttributes, 6> baseAttributes;  // Position in array specifies level.
	EntityAttributes currAttributes;  // Recalculated at begginning of each turn from baseAttributes and effects. (Health uniquely is not recalculated).
	int level = 1;
};

