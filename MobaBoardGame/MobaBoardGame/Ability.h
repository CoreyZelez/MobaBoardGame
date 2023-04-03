#pragma once
#include <assert.h>
#include <memory>
#include <array>
#include "PassiveAbility.h"

class Character;
enum CharacterAction;

class Ability : public CharacterObserver
{
public:
	Ability(int range, int pointCost, double abilityPowerRatio);
	Ability(int range, int pointCost, std::array<double, 3> abilityPowerRatios);

	virtual std::unique_ptr<Ability> clone() = 0;  // Allows for copying of unique_ptrs to base class.

	void initCharacter(Character &character);  // Calls init character on the passive ability.

	// getters
	int getLevel() const;
	int getRange() const;
	int getPointCost() const;
	bool onCooldown() const;
	std::array<double, 3> getAbilityPowerRatios() const;

	// Ability functions for each target type
	bool use(Character &target);
	bool use(Minion &target);

	// State functions
	virtual void update() {}; // Called at start of each turn. Doesn't change duration.
	virtual void reduceCooldown();

protected:
	// Getters
	int getTrueAbilityPower() const;  // True ability power on non target abilities (or sub-abilities).
	int getTrueAbilityPower(Character &target) const;  // True ability power on target abilities (or sub-abilities).
	Character* const getCharacter();

	// Target validation functions.
	virtual bool validTarget(Character &target) { return false;  };
	virtual bool validTarget(Minion &target) { return false; }

	// Need creature target validation function here.

	// Ability apply logic.
	virtual void applySelf() {};  // Effects on caster.
	virtual void applyTarget(Character &target) {};  // Effects on target. Returns boolean on whether target is valid.
	virtual void applyTarget(Minion &target) {};  // Effects on target. Returns boolean on whether target is valid.
	virtual int calculateCooldown() const = 0;  // Cooldown after ability use.

private:
	// Attributes.
	Character *character;
	double range;
	std::array<double, 3> abilityPowerRatios;  // For each level.
	int pointCost = 2;  // Consumes attack and action points.
	int level = 1;  // 1 for testing. should be 0.
	int cooldown = 0;
};






