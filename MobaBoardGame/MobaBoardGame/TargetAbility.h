#pragma once
#include "Ability.h"

template<class T> class TargetAbility : public Ability
{
static_assert(std::is_base_of<Entity, T>::value, "T must inherit boost::archive::text_oarchive");

public:
	bool validTarget(const Entity *entity)  // Ensures that entity parameter is of type T.
	{
		return true;
	}

	void useAbility(Character &caster, Entity &target)  // Applys ability to caster and target if target underlying type is T.
	{
		if(validTarget(target))
		{
			// Code here should upcast/downcast target to type T
			apply(caster, target);  // target is placeholder. should be different variable there.
		}
	}

protected:
	virtual void applySelf(Character &caster) {};  // Effects on caster.
	virtual void applyTarget(T &target) {};  // Effects on target.
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

