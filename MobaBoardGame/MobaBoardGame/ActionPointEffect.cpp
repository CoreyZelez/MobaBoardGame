#include "ActionPointEffect.h"
#include "Character.h"

ActionPointEffect::ActionPointEffect(int duration, int amount)
	: Effect<EntityAttributes>(duration), amount(amount)
{
}

std::unique_ptr<Effect<EntityAttributes>> ActionPointEffect::clone()
{
	return std::make_unique<ActionPointEffect>(*this);
}

void ActionPointEffect::apply(EntityAttributes &ea)
{
	ea.actionAttributes.points += amount;
}
