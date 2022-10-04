#pragma once
#include <memory>
#include "Effect.h"
#include "Attributes.h"

class ParalyseEffect : public Effect<CharacterAttributes>
{
public:
	ParalyseEffect(int duration);

	std::unique_ptr<Effect<CharacterAttributes>> clone();

private:
	void apply(CharacterAttributes &ca);  // Deals health damage.
};

