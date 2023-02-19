#pragma once
#include <array>
#include "PassiveAbility.h"

/* Upon reaching stacks, next basic attack is void shot that slows target and deals true damage over time.
 Damage bonus to a void shot on a voidInflicted target. */
class VoidShotPassive : public PassiveAbility
{
public:
	VoidShotPassive(std::array<int, 6> trueDamage, int stackTrigger, int duration);

	std::unique_ptr<PassiveAbility> clone();

	void update(CharacterAction action);
	void update(CharacterAction action, Character &target);
	void update(CharacterAction action, Creature *target);

private:
	int stackTrigger;  // Num stacks to get enhanced attack.
	int duration = 4;  // How many turns the enhanced attack can be held.
	int stacks = 0;  // Basic attacks grant stacks.
	std::array<int, 6> trueDamage;  // Total true damage applied over duration for a given character level.
};


