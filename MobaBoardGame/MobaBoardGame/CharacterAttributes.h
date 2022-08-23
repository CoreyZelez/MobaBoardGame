#pragma once
#include "Attributes.h"
class CharacterAttributes
{
public:
	CharacterAttributes(ActionAttributes actionA, HealthAttributes healthA, CombatAttributes combatA, AbilityAttributes abilityA);

private:
	ActionAttributes actionAttributes;
	HealthAttributes healthAttributes;
	CombatAttributes combatAttributes;
	AbilityAttributes abilityAttributes;
};

