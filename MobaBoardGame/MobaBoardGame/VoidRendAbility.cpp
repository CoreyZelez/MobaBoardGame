#include "VoidRendAbility.h"
#include "Character.h"
#include "PhysicalDamageEffect.h"
#include "ArmorEffect.h"

VoidRendAbility::VoidRendAbility(std::array<double, 3> levelValues, int duration)
	: Ability(levelValues, range, abilityPowerRatio), duration(duration)
{
}

/* Level values are for physicalAttack reduction applied to target. */
VoidRendAbility::VoidRendAbility(std::array<double, 3> levelValues, int duration, double armorMultiplier)
	: Ability(levelValues, range, abilityPowerRatio), duration(duration), armorMultiplier(armorMultiplier)
{
}

std::unique_ptr<Ability> VoidRendAbility::clone()
{
	return std::make_unique<VoidRendAbility>(*this);
}

void VoidRendAbility::update(TargetCharacterAction action, Character & target)
{

}

bool VoidRendAbility::validTarget(Character &target)
{
	return &target != getCharacter();
}

void VoidRendAbility::applyTarget(Character &target)
{
	const int level = getLevel() - 1;
	assert(level >= 0);

	// Calculation of effects on target.
	const double multiplier = calculateAbilityMultiplier(*getCharacter(), target);
	int pdAmount = -getTrueValue() * multiplier;
	int armorAmount = -getTrueValue() * multiplier * armorMultiplier;

	std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<PhysicalDamageEffect>(duration, pdAmount, voidInfliction);
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<ArmorEffect>(duration, armorAmount, voidInfliction);
	target.addEffect(effect1);
	target.addEffect(effect2);

	// Absorption of stats for self.
	armorAmount *= selfMultiplier;
	pdAmount *= selfMultiplier;
	std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<PhysicalDamageEffect>(duration, pdAmount, voidInfliction);
	std::unique_ptr<Effect<EntityAttributes>> effect4 = std::make_unique<ArmorEffect>(duration, selfMultiplier, voidInfliction);
	getCharacter()->addEffect(effect3);
	getCharacter()->addEffect(effect4);
}

int VoidRendAbility::calculateCooldown() const
{
	return 17;
}
