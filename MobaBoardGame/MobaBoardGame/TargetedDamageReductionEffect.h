#pragma once
#include "Effect.h"
#include "EntityAttributes.h"
#include "CharacterObserver.h"

/* Reduces damage for a specific target.*/
class TargetedDamageReductionEffect : 
	public Effect<EntityAttributes>, public CharacterObserver
{
public:
	TargetedDamageReductionEffect(int duration, double damageReductionRatio, Character& sender, Character &receiver);
	~TargetedDamageReductionEffect();

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void update(CharacterAction action, Character &character);

protected:
	void apply() {};

private:
	const double damageReductionRatio;  // Stat reduction against target.
};

