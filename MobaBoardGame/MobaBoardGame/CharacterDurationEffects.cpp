#include "CharacterDurationEffects.h"

void CharacterDurationEffects::add(std::unique_ptr<HealthDurationEffect> healthEffect)
{
	healthEffects.emplace_back(std::move(healthEffect));
}

void CharacterDurationEffects::add(std::unique_ptr<ActionDurationEffect> actionEffect)
{
	actionEffects.emplace_back(std::move(actionEffect));
}

void CharacterDurationEffects::add(std::unique_ptr<MagicDurationEffect> magicEffect)
{
	magicEffects.emplace_back(std::move(magicEffect));
}

void CharacterDurationEffects::add(std::unique_ptr<CombatDurationEffect> combatEffect)
{
	combatEffects.emplace_back(std::move(combatEffect));
}
