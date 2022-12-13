#pragma once

enum CharacterAction
{
	preReceiveCharacterBasicAttack,
	postReceiveCharacterBasicAttack,

	death
};

enum TargetCharacterAction
{
	preBasicAttackCharacter,
	postBasicAttackCharacter,
	killCharacter
};

enum TargetCreatureAction
{
	preBasicAttackCreature,
	postBasicAttackCreature,
};