#pragma once
#include "Effect.h"

class Character;
struct EntityAttributes;

class HealthDrainEffect : public Effect<EntityAttributes>
{
public:
	HealthDrainEffect(int duration, int amountPT, double absorbRatio, Character &sender);

	std::unique_ptr<Effect<EntityAttributes>> clone();

protected:
	void apply(EntityAttributes &ea);

private:
	const int amountPT;  // Amount of health lost per turn.
	const double absorbRatio;  // Percent of health lost that is transfered to drainer.
};

