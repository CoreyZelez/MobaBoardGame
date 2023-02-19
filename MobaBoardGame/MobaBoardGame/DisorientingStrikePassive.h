#pragma once
#include "Character.h"
#include <memory>

/* Basic attacks "disorient" character targets, causing them to lose 1 movement and action points.
If target health is less than half, lose 2 movement and 1 action point.*/
class DisorientingStrikePassive : public PassiveAbility
{
public:
	DisorientingStrikePassive() = default;

	std::unique_ptr<PassiveAbility> clone();

	void update(CharacterAction action, Character &target);

private:

};

