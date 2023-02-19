#include "CharacterAttributesSystem.h"
#include "CharacterEffectsManager.h"
#include <iostream>

const int NUM_CHARACTER_LEVELS = 6;

void CharacterAttributesSystem::levelUp()
{
	// implement.
}

CharacterAttributesSystem::CharacterAttributesSystem(Character &character, std::vector<EntityAttributes> coreBaseAttributes)
	: AttributesSystem<Character>(std::make_unique<CharacterEffectsManager>(character), coreBaseAttributes)
{

}


