#pragma once
#include <vector>
#include "Entity.h"
#include "Character.h"
#include "Effect.h"


template<class T> class Ability
{
	static_assert(std::is_base_of<Entity, T>::value, "T must inherit boost::archive::text_oarchive");

public:
    bool validTarget(const Entity *entity)  // Ensures that entity parameter is of type T.
	{

	}

	void useAbility(Character &caster, Entity &target)  // Applys ability to caster and target if target underlying type is T.
	{
		if(validTarget(target))
		{
			apply(caster, target);
		}
	}

protected:
	virtual void applySelf(Character &caster) {};  // Effects on caster.
	virtual void applyTarget(Character &target) {};  // Effects on target.
	virtual int calculateCooldown(Character &caster) = 0;  // Cooldown after ability use.

private:
	void apply(Character &caster, T target)
	{
		applySelf(caster);
		applyTarget(target);
		cooldown = calculateCooldown(caster);
	}

	int cooldown = 0;
};







