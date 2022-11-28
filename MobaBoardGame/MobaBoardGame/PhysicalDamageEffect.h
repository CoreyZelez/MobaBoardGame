#pragma once
#include "Effect.h"
#include "Attributes.h"

class PhysicalDamageEffect : public Effect<EntityAttributes>
{
public:
	PhysicalDamageEffect(int duration, int amount);
	PhysicalDamageEffect(int duration, int amount, EffectType type);


	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.

private:
	int amount;  // Damage stat increase.
};

