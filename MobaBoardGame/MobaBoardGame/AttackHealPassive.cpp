#include <iostream>
#include "AttackHealPassive.h"
#include "Character.h"
#include "HealthEffect.h"



AttackHealPassive::AttackHealPassive(int characterStack, int creatureMinionStack)
	: creatureMinionStack(creatureMinionStack), characterStack(characterStack)
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

void AttackHealPassive::update(CharacterAction action, Character &target)
{
	if(action == postBasicAttackDamageDealt)
	{
		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(1, stacks, *getCharacter());
		getCharacter()->addEffect(std::move(healthEffect));
		stacks += characterStack;
	}
}

void AttackHealPassive::update(CharacterAction action, Minion &target)
{
	if(action == postBasicAttackDamageDealt)
	{
		const int healthIncrease = stacks * creatureMinionMultiplier;
		assert(healthIncrease >= 0);

		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(1, healthIncrease, *getCharacter());
		getCharacter()->addEffect(std::move(healthEffect));
		stacks += creatureMinionStack;
	}
}

void AttackHealPassive::update(CharacterAction action, Creature *target)
{
	if(action == postBasicAttackDamageDealt)
	{
		const int healthIncrease = stacks * creatureMinionMultiplier;
		assert(healthIncrease >= 0);

		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(1, healthIncrease, *getCharacter());
		getCharacter()->addEffect(std::move(healthEffect));
		stacks += creatureMinionStack;
	}
}



