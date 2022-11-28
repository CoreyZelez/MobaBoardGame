#include "PhysicalDamageEffect.h"

PhysicalDamageEffect::PhysicalDamageEffect(int duration, int amount)
	: Effect<EntityAttributes>(duration), amount(amount)
{
}

PhysicalDamageEffect::PhysicalDamageEffect(int duration, int amount, EffectType type)
	: Effect<EntityAttributes>(duration, type), amount(amount)
{
}

std::unique_ptr<Effect<EntityAttributes>> PhysicalDamageEffect::clone()
{
	return std::make_unique<PhysicalDamageEffect>(*this);
}

void PhysicalDamageEffect::apply(EntityAttributes &ea)
{
	ea.combatAttributes.physicalDamage += amount;
}
