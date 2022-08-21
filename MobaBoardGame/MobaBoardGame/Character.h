#pragma once
#include <vector>
#include <array>
#include "CharacterAttributes.h"
#include "Item.h"

class Character
{
	using duration = unsigned int;

public:
	Character(std::array<CharacterAttributes, 8> baseAttributes);

private:
	std::array<CharacterAttributes, 8> baseAttributes;  // Attributes of character under no effects. Position in array specifies level.
	std::vector<std::pair<CharacterAttributes, duration>> tempAttributes;  
	std::array<Item, 4> items;

	const static std::array<unsigned int, 7> experienceForLevel;

	unsigned int experience = 0;

};

