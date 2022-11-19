#pragma once
#include "Effect.h"

class Character;
struct CharacterAttributes;

class HealthDrainEffect : public Effect<CharacterAttributes>
{
public:
	HealthDrainEffect(int duration, int amountPT, double absorbRatio, Character &absorber);

	std::unique_ptr<Effect<CharacterAttributes>> clone();

private:
	void apply(CharacterAttributes &ca);  

	const int amountPT;  // Amount of health lost per turn.
	const double absorbRatio;  // Percent of health lost that is transfered to drainer.
	Character &absorber;  // Gains health as it is drained from character effect is applied to.
};

