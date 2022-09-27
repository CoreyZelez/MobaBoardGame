#include "PassiveAbility.h"

/** 
 * selfEffects are applied at the beginning of every turn to the character.
 *
 *
 *
 *
 *
 */
PassiveAbility::PassiveAbility(std::list<std::unique_ptr<CharacterEffect>> selfEffects)
	: Ability(selfEffects)
{
}

void PassiveAbility::notify(CharacterEvent event)
{
}

void PassiveAbility::apply()
{
}
