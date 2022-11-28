#include "BloodAnguishAbility.h"
#include <memory>
#include <iostream>
#include "ActionPointEffect.h"
#include "MovementPointEffect.h"
#include "AttackPointEffect.h"
#include "PhysicalDamageEffect.h"
#include "healthEffect.h"




BloodAnguishAbility::BloodAnguishAbility(std::array<double, 3> levelValues)
	: SelfAbility(levelValues, 0)
{

}


std::unique_ptr<Ability> BloodAnguishAbility::clone()
{
	return std::make_unique<BloodAnguishAbility>(getLevelValues());
}

void BloodAnguishAbility::applySelf()
{
	// insert code 
	active = true;

	std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ActionPointEffect>(1, 3);
	getCharacter()->addEffect(effect1);
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<MovementPointEffect>(1, 3);
	getCharacter()->addEffect(effect2);
	std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<AttackPointEffect>(1, 2);
	getCharacter()->addEffect(effect3);
}

int BloodAnguishAbility::calculateCooldown() const
{
	return 18;
}

void BloodAnguishAbility::update(CharacterAction action)
{
	if(!active)
	{
		return;
	}

	if(action == killCharacter)
	{
		std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ActionPointEffect>(1, 2);
		getCharacter()->addEffect(effect1);
		std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<MovementPointEffect>(1, 2);
		getCharacter()->addEffect(effect2);
		std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<AttackPointEffect>(1, 2);
		getCharacter()->addEffect(effect3);
	}
}

void BloodAnguishAbility::update(TargetCharacterAction action, Character &target)
{
	if(!active)
	{
		return;
	}

	if(action == preBasicAttackCharacter)
	{
		// Determine ratio to add physical damage stats to character. Dependant on target health. 
		// Ignores magic penetration and resist.
		const double abilityPowerRatio = getLevelValues()[getCharacter()->getLevel()];
		health = target.getAttributes().healthAttributes.health;
		const int maxHealth = target.getBaseAttributes().healthAttributes.health;
		double healthRatio = ((double)maxHealth / (double)health);
		const int abilityPower = getCharacter()->getAttributes().abilityAttributes.abilityPower;
		const double abilityPowerMultiplier = 1 + abilityPower * abilityPowerRatio;

		if(healthRatio > 3)
		{
			healthRatio = 3;
		}
		const double finalRatio = healthRatio * abilityPowerMultiplier * 0.5;

		// Adds physical damage to character.
		const int physicalDamage = getCharacter()->getAttributes().combatAttributes.physicalDamage;
		const int amount = physicalDamage * finalRatio;
		std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<PhysicalDamageEffect>(1, amount);
		getCharacter()->addEffect(effect);
	}
	else if(action == postBasicAttackCharacter)
	{
		// Character absorbs all damage from basic attack.
		const int currHealth = target.getAttributes().healthAttributes.health;
		if(currHealth < 0)
		{
			std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<PhysicalDamageEffect>(1, health);
			getCharacter()->addEffect(effect);
		}
		else
		{
			const int healthDiff = health - currHealth;
			std::cout << healthDiff;
			assert(healthDiff > 0);
			std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<HealthEffect>(1, healthDiff);
			getCharacter()->addEffect(effect);
		}
	}
}

void BloodAnguishAbility::update()
{
	active = false;  // Passive only active for a single turn.
}




