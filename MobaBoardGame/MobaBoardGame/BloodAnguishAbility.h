#pragma once
#include "SelfAbility.h"

/* Increase character physical damage stats prior to basic attack scaling with low target health. 
Gain movement and attack points on kill.
Power scales based on how low enemy health is. Gain movement and attack points on kill.*/
class BloodAnguishAbility : public SelfAbility
{
public:
	explicit BloodAnguishAbility(std::array<double, 3> abilityPowerRatios);

	std::unique_ptr<Ability> clone(); 
	void update();  // End of turn update.

	// Observer functions.
	void update(CharacterAction action, Character &target);
	void update(CharacterAction action, int quantity);

protected:
	void applySelf();
	int calculateCooldown() const;

private:
	bool active = false;
	int physicalDamageIncrease = 0;  // For keeping track for pre and post basic attack.
};

