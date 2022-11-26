#include "EnhancedBasicPassive.h"
#include "PhysicalDamageEffect.h"
#include "Character.h"

EnhancedBasicPassive::EnhancedBasicPassive(double damageMultiplier,
	int attackNumTrigger, int duration)
	: damageMultiplier(damageMultiplier), 
	stackTrigger(stackTrigger), duration(duration)
{
}

std::unique_ptr<PassiveAbility> EnhancedBasicPassive::clone()
{
	return std::make_unique<EnhancedBasicPassive>(*this);
}

void EnhancedBasicPassive::update(CharacterAction action)
{
	if(action == preBasicAttackCharacter || action == preBasicAttackCreature)
	{
		// Store damage increase so damage can be deducted post attack.
		attackIncrease = getCharacter()->getAttributes().combatAttributes.physicalDamage * (damageMultiplier - 1);

		// Increase damage prior to basic attack.
		PhysicalDamageEffect damageEff(1, attackIncrease);
		std::unique_ptr<Effect<EntityAttributes>> damageEffect = std::make_unique<PhysicalDamageEffect>(damageEff);
		getCharacter()->addEffect(damageEffect);
	}
	else if(action == postBasicAttackCharacter || preBasicAttackCreature)
	{
		// Decrease damage to pre attack levels.
		PhysicalDamageEffect damageEff(1, -attackIncrease);
		std::unique_ptr<Effect<EntityAttributes>> damageEffect = std::make_unique<PhysicalDamageEffect>(damageEff);
		getCharacter()->addEffect(damageEffect);
	}
}
