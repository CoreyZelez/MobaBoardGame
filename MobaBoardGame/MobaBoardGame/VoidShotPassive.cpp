#include <iostream>
#include "VoidShotPassive.h"
#include "HealthEffect.h"
#include "MovementPointEffect.h"
#include "ActionPointEffect.h"
#include "Character.h"


VoidShotPassive::VoidShotPassive(std::array<int, 6> trueDamage, int stackTrigger, int duration)
	: trueDamage(trueDamage), stackTrigger(stackTrigger), duration(duration)
{
}

std::unique_ptr<PassiveAbility> VoidShotPassive::clone()
{
	return std::make_unique<VoidShotPassive>(*this);
}

void VoidShotPassive::update(TargetCharacterAction action, Character &target)
{
	if(stacks == stackTrigger && action == preBasicAttackCharacter)
	{
		stacks = 0;

		// True damage effect.
		const int level = getCharacter()->getLevel() - 1;
		const int damage = trueDamage[level];
		const int damagePerTurn = (double)damage / (double)duration;

		std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<HealthEffect>(duration, -damagePerTurn);
		std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<ActionPointEffect>(duration, -1);
		std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<MovementPointEffect>(duration, -1);

		target.addEffect(effect1);
		target.addEffect(effect2);
		target.addEffect(effect3);
	}
	else if(action == preBasicAttackCharacter)
	{
		++stacks;
	}
}

void VoidShotPassive::update(TargetCreatureAction action, Creature *target)
{
	if(stacks == stackTrigger && action == preBasicAttackCreature)
	{
		stacks = 0;
		// To be implemented. Creatures dont receive slow and action effects.
	}
	else if(action == preBasicAttackCreature)
	{
		++stacks;
	}
}
