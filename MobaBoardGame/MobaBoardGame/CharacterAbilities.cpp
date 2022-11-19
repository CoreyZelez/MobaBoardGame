#include "CharacterAbilities.h"

CharacterAbilities::CharacterAbilities(AbilityArsenal arsenal)
	: passive(arsenal.passive->clone()),
	ability1(arsenal.ability1->clone()),
	ability2(arsenal.ability2->clone())
{
}
