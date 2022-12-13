#include <iostream>
#include "AttackHealPassive.h"
#include "Character.h"
#include "HealthEffect.h"



AttackHealPassive::AttackHealPassive(int characterStack, int creatureStack)
	: creatureStack(creatureStack), characterStack(characterStack)
{
}

AttackHealPassive::AttackHealPassive()
	: AttackHealPassive(1, 2)
{
}

void AttackHealPassive::update()
{
	stacks -= decayAmount;
	if(stacks < 0)
	{
		stacks = 0;
	}
}

void AttackHealPassive::update(CharacterAction action)
{
	if(action == death)
	{
		stacks = 0;
	}
}

std::unique_ptr<PassiveAbility> AttackHealPassive::clone()
{
	return std::make_unique<AttackHealPassive>(*this);
}

void AttackHealPassive::update(TargetCharacterAction action, Character &target)
{
	if(action == postBasicAttackCharacter)
	{
		const int maxHealth = getCharacter()->getBaseAttributes().healthAttributes.health;
		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(1, stacks, maxHealth);
		getCharacter()->addEffect(healthEffect);
		stacks += characterStack;
	}
}

void AttackHealPassive::update(TargetCreatureAction action, Creature *target)
{
	if(action == postBasicAttackCreature)
	{
		const int healthIncrease = stacks * creatureMultiplier;
		assert(healthIncrease >= 0);

		const int maxHealth = getCharacter()->getBaseAttributes().healthAttributes.health;
		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(1, healthIncrease, maxHealth);
		getCharacter()->addEffect(healthEffect);
		stacks += creatureStack;
	}
}



