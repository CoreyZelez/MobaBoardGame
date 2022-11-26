#pragma once

enum CharacterAction
{
	preReceiveCharacterBasicAttack,
	postReceiveCharacterBasicAttack,

	death,

	killCharacter
};

enum TargetCharacterAction
{
	preBasicAttackCharacter,
	postBasicAttackCharacter,
};

enum TargetCreatureAction
{
	preBasicAttackCreature,
	postBasicAttackCreature,
};