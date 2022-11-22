#include <memory>
#include "HealthEffect.h"
#include "Attributes.h"

struct CharacterAttributes;

HealthEffect::HealthEffect(int duration, int amountPT)
	: Effect<CharacterAttributes>(duration), amountPT(amountPT)
{
}

std::unique_ptr<Effect<CharacterAttributes>> HealthEffect::clone()
{
	return std::make_unique<HealthEffect>(*this);
}

void HealthEffect::apply(CharacterAttributes &ca)
{
	ca.healthAttributes.health += amountPT;
}
