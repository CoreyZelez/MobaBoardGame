#pragma once
#include "EntityAttributes.h"
#include "StatusEffect.h"

class Minion;

class MinionAttributesSystem
{
public:
	using EntityEffect = Effect<EntityAttributes>;

public:
	MinionAttributesSystem(Minion &minion, EntityAttributes baseAttributes);

	EntityAttributes& getAttributes();
	EntityAttributes getAttributes() const;
	EntityAttributes getBaseAttributes() const;
	int getLevel() const;

	void update();

	bool isAlive() const;
	bool hasEffectType(Status type) const;

	void addEffect(std::unique_ptr<EntityEffect> &effect);
	void addStatusEffect(int duration, Status type);
	void reset();

private:
	void resetCurrAttributes();

	Minion &minion;

	EntityAttributes baseAttributes;  // Changed upon minion merges.
	EntityAttributes currAttributes;  // Recalculated at begginning of each turn from baseAttributes and effects. (Health uniquely is not recalculated).

	MinionEffectsManager effects;
};

