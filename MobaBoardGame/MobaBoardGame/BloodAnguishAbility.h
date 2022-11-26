#pragma once
#include "SelfAbility.h"

/* Power scales based on how low enemy health is. Gain movement and attack points on kill.*/
class BloodAnguishAbility : public SelfAbility
{
public:
	explicit BloodAnguishAbility(std::array<double, 3> levelValues);

	std::unique_ptr<Ability> clone();  

	void update(CharacterAction action);
	void update(TargetCharacterAction action, Character &target);  // Use when you need to add 
	void update();

protected:
	void applySelf();
	int calculateCooldown() const;

private:
	bool active = false;
	int health;  // Health prior to attacking character with passive active.
};

