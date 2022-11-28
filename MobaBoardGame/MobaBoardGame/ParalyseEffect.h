#pragma once
#include <memory>
#include "Effect.h"
#include "Attributes.h"

class ParalyseEffect : public Effect<EntityAttributes>
{
public:
	ParalyseEffect(int duration);
	ParalyseEffect(int duration, EffectType type);


	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.
};

