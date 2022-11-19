#pragma once
#include <assert.h>
#include <memory>
#include "PassiveAbility.h"

class Character;
enum CharacterAction;

class Ability 
{
public:
	Ability(Character &character);
	Ability(PassiveAbility *passive);
	virtual std::unique_ptr<Ability> clone() = 0;  // Allows for copying of unique_ptrs to base class.

	// Ability functions for each target type.
	bool use(Character &target);

protected:
	// Target validation functions.
	virtual bool validTarget(Character &target) { return false; }

	// Ability effect logic.
	virtual void applySelf(Character &owner) {};  // Effects on caster.
	virtual void applyTarget(Character &owner, Character &target) {};  // Effects on target. Returns boolean on whether target is valid.
	void applyPassive();

	virtual int calculateCooldown(Character &owner) = 0;  // Cooldown after ability use.

	const Character *getOwner();

private:
	std::unique_ptr<PassiveAbility> passive;
	int level = 0;
	int cooldown = 0;
};






