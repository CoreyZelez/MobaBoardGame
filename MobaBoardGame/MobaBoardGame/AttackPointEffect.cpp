#include "AttackPointEffect.h"

AttackPointEffect::AttackPointEffect(int duration, int amount)
	: Effect<EntityAttributes>(duration), amount(amount)
{
}

std::unique_ptr<Effect<EntityAttributes>> AttackPointEffect::clone()
{
	return std::make_unique<AttackPointEffect>(*this);
}

void AttackPointEffect::apply()
{
	EntityAttributes &ea = getT();
	ea.actionAttributes.attackPoints += amount;
}
