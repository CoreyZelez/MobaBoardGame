#include "HealthPoisonEffect.h"
#include "Attributes.h"

struct CharacterAttributes;

HealthPoisonEffect::HealthPoisonEffect(int duration, int amountPT)
	: Effect<CharacterAttributes>(duration), amountPT(amountPT)
{
}

std::unique_ptr<Effect<CharacterAttributes>> HealthPoisonEffect::clone()
{
	return std::make_unique<HealthPoisonEffect>(*this);
}

void HealthPoisonEffect::apply(CharacterAttributes &ca)
{
	ca.healthAttributes.health -= amountPT;
}
