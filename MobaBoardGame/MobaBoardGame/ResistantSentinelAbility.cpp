#include "ResistantSentinelAbility.h"
#include "MovementPointEffect.h"
#include "ArmorEffect.h"
#include "AbilityResistEffect.h"



ResistantSentinelAbility::ResistantSentinelAbility(std::array<double, 3> armorIncreases, std::array<double, 3> magicResistIncreases)
	: SelfAbility(0, 1), armorIncreases(armorIncreases), magicResistIncreases(magicResistIncreases)
{
}

std::unique_ptr<Ability> ResistantSentinelAbility::clone()
{
	return std::make_unique<ResistantSentinelAbility>(armorIncreases, magicResistIncreases);
}

void ResistantSentinelAbility::applySelf()
{
	const int level = getLevel() - 1;
	int armorAmount = getTrueAbilityPower() + armorIncreases[level];
	int magicResistAmount = getTrueAbilityPower() + magicResistIncreases[level];

	std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<MovementPointEffect>(4, -3);
	getCharacter()->addEffect(std::move(effect1));
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<ArmorEffect>(4, armorAmount);
	getCharacter()->addEffect(std::move(effect2));
	std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<AbilityResistEffect>(4, magicResistAmount);
	getCharacter()->addEffect(std::move(effect3));

}

int ResistantSentinelAbility::calculateCooldown() const
{
	return 12;
}
