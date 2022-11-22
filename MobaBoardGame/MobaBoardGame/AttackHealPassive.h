#pragma once
#include <memory>
#include "PassiveAbility.h"

class AttackHealPassive : public PassiveAbility 
{
public:
	AttackHealPassive(int creatureStack, int characterStack, int creatureMultiplier);
	AttackHealPassive();
	std::unique_ptr<PassiveAbility> clone();

	void update(CharacterAction action);

private:
	double creatureMultiplier = 0;  // Less heal from creatures.
	int creatureStack;
	int characterStack;
	int stacks = 0;
};

