#include "Character.h"

const std::array<unsigned int, 7> Character::experienceForLevel = { 0, 20, 45, 80, 130, 200, 300 };

Character::Character(std::array<CharacterAttributes, 8> baseAttributes)
	: baseAttributes(baseAttributes)
{
}
