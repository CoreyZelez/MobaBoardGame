#include "BloodAnguishAbility.h"
#include <memory>
#include <iostream>
#include "ActionPointEffect.h"
#include "MovementPointEffect.h"
#include "AttackPointEffect.h"
#include "PhysicalDamageEffect.h"
#include "HealthEffect.h"


BloodAnguishAbility::BloodAnguishAbility(std::array<double, 3> abilityPowerRatios)
	: SelfAbility(0, abilityPowerRatios)
{

}

std::unique_ptr<Ability> BloodAnguishAbility::clone()
{
	return std::make_unique<BloodAnguishAbility>(getAbilityPowerRatios());
}

void BloodAnguishAbility::applySelf()
{
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
	return 22;
}

void BloodAnguishAbility::update(TargetCharacterAction action, Character &target)
{
	if(!active)
	{
		return;
	}

	if(action == preBasicAttackCharacter)
	{
		// Determine ratio to add physical damage stats to character. Dependant on target health and magic stats of both characters. 
		health = target.getAttributes().healthAttributes.health;  // Stores health of target prior to attack for health absorbtion calculation.
		const int maxHealth = target.getBaseAttributes().healthAttributes.health;
		double healthRatio = ((double)maxHealth / (double)health);

		const int trueAbilityPower = getTrueAbilityPower(target);
		const double powerMultiplier = 1 + trueAbilityPower;  // TrueAbilityPower is expectedly very small as it is a multiplier of stats.

		if(healthRatio > 3)
		{
			healthRatio = 3;
		}

		// Determine final ratio to multiply physical damage stats by.
		const double reductionFactor = 0.5;
		const double finalRatio = healthRatio * powerMultiplier * reductionFactor;

		// Increase characters physical damage stats.
		const int physicalDamage = getCharacter()->getAttributes().combatAttributes.physicalDamage;
		physicalDamageIncrease = physicalDamage * finalRatio;
		std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<PhysicalDamageEffect>(1, physicalDamageIncrease);
		getCharacter()->addEffect(effect);
	}
	else if(action == postBasicAttackCharacter)
	{
		// Remove physical damage bonus.
		std::unique_ptr<Effect<EntityAttributes>> negateEffect = std::make_unique<PhysicalDamageEffect>(1, -physicalDamageIncrease);
		getCharacter()->addEffect(negateEffect);
		physicalDamageIncrease = 0;

		// Character absorbs all damage from basic attack.
		const int currHealth = target.getAttributes().healthAttributes.health;
		if(currHealth < 0)
		{
			const int maxHealth = getCharacter()->getBaseAttributes().healthAttributes.health;
			std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<HealthEffect>(1, health, maxHealth);
			getCharacter()->addEffect(effect);
		}
		else
		{
			const int healthDiff = health - currHealth;
			const int maxHealth = getCharacter()->getBaseAttributes().healthAttributes.health;
			assert(healthDiff > 0);
			std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<HealthEffect>(1, healthDiff, maxHealth);
			getCharacter()->addEffect(effect);
		}
	}
	else if(action == killCharacter)
	{
		std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ActionPointEffect>(1, 2);
		getCharacter()->addEffect(effect1);
		std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<MovementPointEffect>(1, 2);
		getCharacter()->addEffect(effect2);
		std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<AttackPointEffect>(1, 2);
		getCharacter()->addEffect(effect3);
	}
}

void BloodAnguishAbility::update()
{
	active = false;  // Passive only active for a single turn.
}




