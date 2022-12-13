#pragma once
#include <memory>
#include "Effect.h"
#include "EntityAttributes.h"

class ParalyseEffect : public Effect<EntityAttributes>
{
public:
	ParalyseEffect(int duration);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.
};

