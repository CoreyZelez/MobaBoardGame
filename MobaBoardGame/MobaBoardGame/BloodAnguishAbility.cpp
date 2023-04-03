#include "BloodAnguishAbility.h"
#include <memory>
#include <iostream>
#include "ActionPointEffect.h"
#include "MovementPointEffect.h"
#include "AttackPointEffect.h"
#include "PhysicalDamageEffect.h"
#include "HealthEffect.h"


const int ABSORBTION_RATIO = 0.5;

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
	getCharacter()->addEffect(std::move(effect1));
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<MovementPointEffect>(1, 3);
	getCharacter()->addEffect(std::move(effect2));
	std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<AttackPointEffect>(1, 2);
	getCharacter()->addEffect(std::move(effect3));
}

int BloodAnguishAbility::calculateCooldown() const
{
	return 28;
}

void BloodAnguishAbility::update(CharacterAction action, Character &target)
{
	if(!active)
	{
		return;
	}

	if(action == preBasicAttackDamageCalculation)
	{
		// Determine ratio to add physical damage stats to character. Dependant on target health and magic stats of both characters. 
		const int targetCurrHealth = target.getAttributes().healthAttributes.health;  // Stores health of target prior to attack for health absorbtion calculation.
		const int targetMaxHealth = target.getBaseAttributes().healthAttributes.health;
		double healthRatioReductionFactor = 0.3;
		double healthRatio = ((double)targetMaxHealth / (double)targetCurrHealth) * healthRatioReductionFactor;

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
		assert(physicalDamageIncrease >= 0);
		std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<PhysicalDamageEffect>(1, physicalDamageIncrease);
		getCharacter()->addEffect(std::move(effect));
	}
	else if(action == kill)
	{
		std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ActionPointEffect>(1, 2);
		getCharacter()->addEffect(std::move(effect1));
		std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<MovementPointEffect>(1, 2);
		getCharacter()->addEffect(std::move(effect2));
		std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<AttackPointEffect>(1, 2);
		getCharacter()->addEffect(std::move(effect3));
	}
}

/* 
Quantity parameter specifies true damage dealt from basic attack to character (minion?).
*/
void BloodAnguishAbility::update(CharacterAction action, int quantity)
{
	if(!active)
	{
		return;
	}

	if(action == postBasicAttackDamageDealt)
	{
		assert(quantity >= 0);

		// Remove physical damage bonus.
		std::unique_ptr<Effect<EntityAttributes>> negateEffect = std::make_unique<PhysicalDamageEffect>(1, -physicalDamageIncrease);
		getCharacter()->addEffect(std::move(negateEffect));
		physicalDamageIncrease = 0;

		// Add health effect.
		quantity *= ABSORBTION_RATIO;  // Half of health damage is absorbed.
		std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<HealthEffect>(1, quantity, *getCharacter());
		getCharacter()->addEffect(std::move(effect));
	}
}

void BloodAnguishAbility::update()
{
	active = false;  // Passive only active for a single turn.
}




