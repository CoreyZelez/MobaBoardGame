#include "DamageEffect.h"

DamageEffect::DamageEffect(int duration, int amount)
	: Effect<CharacterAttributes>(duration), amount(amount)
{
}

std::unique_ptr<Effect<CharacterAttributes>> DamageEffect::clone()
{
	return std::make_unique<DamageEffect>(*this);
}

void DamageEffect::apply(CharacterAttributes &ca)
{
	ca.combatAttributes.physicalDamage += amount;
}
