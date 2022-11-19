#pragma once
#include <vector>
#include "Character.h"
#include "Effect.h"
#include "Ability.h"


class SelfAbility : public Ability
{
public:
	SelfAbility(PassiveAbility *passive);
	virtual std::unique_ptr<Ability> clone() = 0;  // Allows for copying of unique_ptrs to base class.

protected:
	// Target validation functions.
	virtual bool validTarget(Character &target);

	// Ability effect logic.
	virtual void applySelf(Character &owner) {};  // Effects on caster.
	virtual void applyTarget(Character &owner, Character &target) {};  // Effects on target. Returns boolean on whether target is valid.
	virtual int calculateCooldown(Character &owner) = 0;  // Cooldown after ability use.

private:

};







