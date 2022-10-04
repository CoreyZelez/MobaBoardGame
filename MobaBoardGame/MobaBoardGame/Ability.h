#pragma once
#include <vector>
#include "Entity.h"
#include "Character.h"
#include "Effect.h"


class Ability
{
public:
	virtual void useAbility(Character &caster, Entity &target)  // Applys ability to caster and target if target underlying type is T.
	{
		if(&(Entity)caster == &target)  // Should check that caster and target are same object.
		{
			apply(caster);
		}
	}

protected:
	virtual void applySelf(Character &caster) {};  // Effects on caster.
	virtual int calculateCooldown(Character &caster) = 0;  // Cooldown after ability use.

private:
	void apply(Character &caster)
	{
		applySelf(caster);
		cooldown = calculateCooldown(caster);
	}

	int cooldown = 0;
};







