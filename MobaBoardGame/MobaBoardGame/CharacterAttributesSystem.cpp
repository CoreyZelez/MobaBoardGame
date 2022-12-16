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
	EntityAttributes &currAttributes = getAttributes();
	assert(coreBaseAttributes.size() == NUM_CHARACTER_LEVELS);
	const int arrayLevel = getLevel() - 1;
	assert(arrayLevel == 0);  // Can remove for testing purposes.
	currAttributes = getBaseAttributes();  // Current attributes starts at level 0 base attributes.
}


