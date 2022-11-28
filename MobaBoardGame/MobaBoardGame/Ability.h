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
	Ability(std::array<double, 3> levelValues, double range);
	Ability(std::array<double, 3> levelValues, double range, double abilityPowerRatio);

	virtual std::unique_ptr<Ability> clone() = 0;  // Allows for copying of unique_ptrs to base class.

	void initCharacter(Character &character);  // Calls init character on the passive ability.

	int getLevel() const;
	std::array<double, 3> getLevelValues() const;

	// Observer functions.
	virtual void update(CharacterAction action) {};
	virtual void update(TargetCharacterAction action, Character &target) {};  
	virtual void update(TargetCreatureAction action, Creature *target) {};

	// Ability functions for each target type.
	bool use(Character &target);

	virtual void update() {}; // Called at start of each turn.

protected:
	int getTrueValue(); // level value adjusted for ability power.
	double getAbilityPowerRatio() const;
	Character * const getCharacter();

	// Target validation functions.
	virtual bool validTarget(Character &target) = 0;
	// Need creature target validation function here.

	// Ability effect logic.
	virtual void applySelf() {};  // Effects on caster.
	virtual void applyTarget(Character &target) {};  // Effects on target. Returns boolean on whether target is valid.

	virtual int calculateCooldown() const = 0;  // Cooldown after ability use.

private:
	const std::array<double, 3> levelValues;  // Values of some representation of ability magnitude for each 3 levels.
	Character *character;
	double abilityPowerRatio = 0;
	int level = 1;  // 1 for testing. should be 0.
	int cooldown = 0;
	double range = 0;  
};






