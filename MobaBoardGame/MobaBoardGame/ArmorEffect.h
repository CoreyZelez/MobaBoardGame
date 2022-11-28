#pragma once
#include "Effect.h"
#include "Attributes.h"
class ArmorEffect : public Effect<EntityAttributes>
{
public:
	ArmorEffect(int duration, int amount);
	ArmorEffect(int duration, int amount, EffectType type);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.

private:
	int amount;  // Damage stat increase.
};

