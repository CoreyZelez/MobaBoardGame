#include "HealthPoisonEffect.h"

struct CharacterAttributes;

HealthPoisonEffect::HealthPoisonEffect(int duration, int amount)
	: Effect<CharacterAttributes>(duration), amount(amount)
{
}

void HealthPoisonEffect::apply(CharacterAttributes &ca)
{
	ca.healthAttributes.health -= amount;
}
