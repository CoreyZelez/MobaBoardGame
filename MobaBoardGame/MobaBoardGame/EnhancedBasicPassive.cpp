#include "EnhancedBasicPassive.h"
#include "DamageEffect.h"
#include "Character.h"

EnhancedBasicPassive::EnhancedBasicPassive(double damageMultiplier,
	int attackNumTrigger, int duration)
	: damageMultiplier(damageMultiplier), 
	stackTrigger(stackTrigger), duration(duration)
{
}

void EnhancedBasicPassive::update(CharacterAction action)
{
	if(action == preBasicAttackCharacter || action == preBasicAttackMinion)
	{
		// Store damage increase so damage can be deducted post attack.
		attackIncrease = getCharacter()->getAttributes().combatAttributes.physicalDamage * (damageMultiplier - 1);

		// Increase damage prior to basic attack.
		DamageEffect damageEff(1, attackIncrease);
		std::unique_ptr<Effect<CharacterAttributes>> damageEffect = std::make_unique<DamageEffect>(damageEff);
		getCharacter()->addEffect(damageEffect);
	}
	else if(action == postBasicAttackCharacter || postBasicAttackMinion)
	{
		// Decrease damage to pre attack levels.
		DamageEffect damageEff(1, -attackIncrease);
		std::unique_ptr<Effect<CharacterAttributes>> damageEffect = std::make_unique<DamageEffect>(damageEff);
		getCharacter()->addEffect(damageEffect);
	}
}
