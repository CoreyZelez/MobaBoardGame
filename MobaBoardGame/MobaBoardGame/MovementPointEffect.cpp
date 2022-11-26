#include "MovementPointEffect.h"
#include "Character.h"

MovementPointEffect::MovementPointEffect(int duration, int amount)
	: Effect<EntityAttributes>(duration), amount(amount)
{
}

std::unique_ptr<Effect<EntityAttributes>> MovementPointEffect::clone()
{
	return std::make_unique<MovementPointEffect>(*this);
}

void MovementPointEffect::apply(EntityAttributes &ea)
{
	ea.actionAttributes.movementPoints += amount;
}
