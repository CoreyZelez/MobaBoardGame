#include "ArmorEffect.h"

ArmorEffect::ArmorEffect(int duration, int amount)
	: Effect<EntityAttributes>(duration), amount(amount)
{
}

ArmorEffect::ArmorEffect(int duration, int amount, EffectType type)
	: Effect<EntityAttributes>(duration, type), amount(amount)
{
}


std::unique_ptr<Effect<EntityAttributes>> ArmorEffect::clone()
{
	return std::make_unique<ArmorEffect>(*this);
}

void ArmorEffect::apply(EntityAttributes &ea)
{
	ea.combatAttributes.physicalDamage += amount;
}