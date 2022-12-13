#pragma once
#include "Effect.h"
#include "EntityAttributes.h"
class AttackPointEffect : public Effect<EntityAttributes>
{
public:
	AttackPointEffect(int duration, int amount);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.

private:
	int amount;  // attackPoint stat increase.
};
