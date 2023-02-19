#include "AbilityResistEffect.h"

AbilityResistEffect::AbilityResistEffect(int duration, int amount)
	: Effect<EntityAttributes>(duration), amount(amount)
{

}

std::unique_ptr<Effect<EntityAttributes>> AbilityResistEffect::clone()
{
	return std::make_unique<AbilityResistEffect>(*this);
}

void AbilityResistEffect::apply()
{
	EntityAttributes &ea = getT();
	ea.abilityAttributes.abilityResist += amount;
}
