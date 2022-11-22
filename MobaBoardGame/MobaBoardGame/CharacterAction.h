#pragma once

enum CharacterAction
{
	preBasicAttackCharacter,
	postBasicAttackCharacter,

	preBasicAttackMinion,
	postBasicAttackMinion,

	preTakeCharacterDamage,
	postTakeCharacterDamage,

	death,
	killCharacter
};