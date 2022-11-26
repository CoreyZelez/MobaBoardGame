#pragma once
#include <memory>
#include "PassiveAbility.h"

class AttackHealPassive : public PassiveAbility 
{
public:
	AttackHealPassive(int characterStack, int creatureStack);
	AttackHealPassive();
	std::unique_ptr<PassiveAbility> clone();

	void update();  // Called at end of turn.
	void update(CharacterAction action);
	void update(TargetCharacterAction action, Character &target);
	void update(TargetCreatureAction action, Creature *target);

private:
	double creatureMultiplier = 0.5;  // Less heal from creatures.
	int creatureStack;
	int characterStack;
	double stacks = 0;
	const double decayAmount = 0.15;
};

