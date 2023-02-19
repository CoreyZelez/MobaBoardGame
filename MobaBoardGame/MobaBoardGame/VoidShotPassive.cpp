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

void VoidShotPassive::update(CharacterAction action)
{
	if(action == death)
	{
		stacks = 0;
	}
}

void VoidShotPassive::update(CharacterAction action, Character &target)
{
	const int level = getCharacter()->getLevel() - 1;

	if(stacks == stackTrigger && action == preBasicAttackDamageCalculation)
	{
		stacks = 0;

		// True damage effect. Applys damage in excess of normal basic attack damage.
		int damage = trueDamage[level];
		if(target.hasEffectType(voidInfliction))
		{
			damage *= 2;
		}

		const int damagePerTurn = (double)damage / (double)duration;

		std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<HealthEffect>(duration, -damagePerTurn, target);
		std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<ActionPointEffect>(duration, -1);
		std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<MovementPointEffect>(duration, -1);
		target.addEffect(std::move(effect1));
		target.addEffect(std::move(effect2));
		target.addEffect(std::move(effect3));
	}
	else if(action == preBasicAttackDamageCalculation)
	{
		++stacks;

		// True damage when target is voidInflicted but stacks not at trigger. (non void shot).
		if(target.hasEffectType(voidInfliction))
		{
			const double nonVoidShotRate = 0.5;
			const int damage = (double)trueDamage[level] * nonVoidShotRate;
			const int damagePerTurn = (double)damage / (double)duration;
			std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<HealthEffect>(duration, -damagePerTurn, target);
		}
	}
}

void VoidShotPassive::update(CharacterAction action, Creature *target)
{
	if(stacks == stackTrigger && action == preBasicAttackDamageCalculation)
	{
		stacks = 0;
		// To be implemented. Creatures dont receive slow and action effects.
	}
	else if(action == preBasicAttackDamageCalculation)
	{
		++stacks;
	}
}
