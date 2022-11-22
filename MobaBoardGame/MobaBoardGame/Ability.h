#pragma once
#include <assert.h>
#include <memory>
#include <array>
#include "PassiveAbility.h"

class Character;
enum CharacterAction;

class Ability 
{
public:
	Ability(std::array<int, 3> levelValues, int range);
	Ability(std::array<int, 3> levelValues, int range, PassiveAbility *passive);
	virtual std::unique_ptr<Ability> clone() = 0;  // Allows for copying of unique_ptrs to base class.

	int getLevel() const;

	void initCharacter(Character &character);  // Calls init character on the passive ability.

	// Ability functions for each target type.
	bool use(Character &target);

protected:
	std::array<int, 3> getLevelValues() const;

	// Target validation functions.
	virtual bool validTarget(Character &target) = 0;

	// Ability effect logic.
	virtual void applySelf() {};  // Effects on caster.
	virtual void applyTarget(Character &target) const {};  // Effects on target. Returns boolean on whether target is valid.
	void applyPassive();

	virtual int calculateCooldown() const = 0;  // Cooldown after ability use.

	Character *getOwner();

private:
	const std::array<int, 3> levelValues;  // Values of some representation of ability magnitude for each 3 levels.
	std::unique_ptr<PassiveAbility> passive;
	int level = 1;  // 1 for testing. should be 0.
	int cooldown = 0;
	int range = 0;  
};






