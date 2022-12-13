#include "PhysicalDamageEffect.h"
#include <iostream>

PhysicalDamageEffect::PhysicalDamageEffect(int duration, int amount)
	: Effect<EntityAttributes>(duration), amount(amount)
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
