#pragma once
#include <List>
#include <memory>
#include "DurationEffect.h"
#include "Attributes.h"

class CharacterDurationEffects
{
	using HealthDurationEffect = DurationEffect<HealthAttributes>;
	using ActionDurationEffect = DurationEffect<ActionAttributes>;
	using CombatDurationEffect = DurationEffect<CombatAttributes>;
	using MagicDurationEffect = DurationEffect<AbilityAttributes>;

public:
	void add(std::unique_ptr<HealthDurationEffect> healthEffect);
	void add(std::unique_ptr<ActionDurationEffect> actionEffect);
	void add(std::unique_ptr<CombatDurationEffect> combatEffect);
	void add(std::unique_ptr<MagicDurationEffect> magicEffect);


private:
	std::list<std::unique_ptr<HealthDurationEffect>> healthEffects;
	std::list<std::unique_ptr<ActionDurationEffect>> actionEffects;
	std::list<std::unique_ptr<CombatDurationEffect>> combatEffects;
	std::list<std::unique_ptr<MagicDurationEffect>> magicEffects;
};

