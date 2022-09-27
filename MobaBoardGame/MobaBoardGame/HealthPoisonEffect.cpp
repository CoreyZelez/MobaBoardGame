#include "HealthPoisonEffect.h"

struct CharacterAttributes;

HealthPoisonEffect::HealthPoisonEffect(int duration, int amount)
	: Effect<CharacterAttributes>(duration), amount(amount)
{
}

std::unique_ptr<Effect<CharacterAttributes>> HealthPoisonEffect::clone()
{
	return std::make_unique<HealthPoisonEffect>(*this);
}

void HealthPoisonEffect::apply(CharacterAttributes &ca)
{
	ca.healthAttributes.health -= amount;
}
