#pragma once
#include "Effect.h"

struct EntityAttributes;

class MovementPointEffect : public Effect<EntityAttributes>
{
public:
	MovementPointEffect(int duration, int amount);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.

private:
	int amount;  // Damage stat increase.
};

