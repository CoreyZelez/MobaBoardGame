#pragma once

enum CharacterAction
{
	preBasicAttackDamageCalculation,
	preBasicAttackDamageDealt,
	postBasicAttackDamageDealt,

	preAbilityDamageCalculation,
	postAbilityDamageDealt,

	basicAttack,  // is this used?
	kill,
	death
};
