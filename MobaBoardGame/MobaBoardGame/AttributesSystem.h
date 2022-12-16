#pragma once
#include <vector>
#include <iostream>
#include "EffectsManager.h"
#include "EntityAttributes.h"


template<class T>
class AttributesSystem
{
	using EntityEffect = Effect<EntityAttributes>;

public:
	AttributesSystem(std::unique_ptr<EffectsManager<T>> effectsManager, std::vector<EntityAttributes> coreBaseAttributes)
		: effectsManager(std::move(effectsManager))
		, baseAttributes(coreBaseAttributes)
	{
	};

	EntityAttributes& getAttributes() { return currAttributes;  }
	EntityAttributes getAttributes() const { return currAttributes; } 
	EntityAttributes getBaseAttributes() const 
	{ 
		const int levelIndex = level - 1;
		return baseAttributes[levelIndex];
	}

	int getLevel() const { return level; }

	void update()
	{
		updateCurrAttributes();
		effectsManager.get()->update();
	}

	bool isAlive() const { return currAttributes.healthAttributes.health > 0; }

	bool hasEffectType(Status type) const { return effectsManager.get()->hasEffectType(type); }

	void addEffect(std::unique_ptr<EntityEffect> &effect)
	{
		// Applys effect and updates it.
		effect.get()->update(currAttributes);

		// Adds effect if duration not 0 after initial update.
		if(!effect.get()->isOver())
		{
			effectsManager.get()->add(effect);
		}
	}

	void addStatusEffect(int duration, Status type) { effectsManager.get()->add(duration, type); }

	void deathReset()
	{
		assert(currAttributes.healthAttributes.health <= 0);

		const int level = getLevel() - 1;
		currAttributes = baseAttributes[level];

		effectsManager.get()->clear();
	}

	virtual void levelUp() { ++level; }  // Override to include logic for handling experience.

protected:
	T& getSubject() { return effectsManager.getSubject(); }

	void updateCurrAttributes()
	{
		// IN FUTURE NEED TO INCORPORATE ITEMS.
		///////////////////////////////////////

		EntityAttributes &currAttributes = getAttributes();
		const int level = getLevel() - 1;
		const int health = currAttributes.healthAttributes.health;  // Health is not recalculated.
		currAttributes = getBaseAttributes();
		assert(health <= currAttributes.healthAttributes.health);  // Health cannot be more than base health.
		currAttributes.healthAttributes.health = health;
	}

private:

	EntityAttributes currAttributes; 
	std::vector<EntityAttributes> baseAttributes;  // size of vector is number of levels.
	int level = 1;

	std::unique_ptr<EffectsManager<T>> effectsManager;
};

