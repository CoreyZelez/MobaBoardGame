#pragma once
#include <memory>

class Character;
struct Position;

class CharacterFactory
{
public:
	std::shared_ptr<Character> createBloodlordKlaus(Position initPos, double multiplier);  // Assassin with focus on lifesteal (JGL).
	std::shared_ptr<Character> createVoidArcherLeanna(Position initPos, double multiplier);  // Assassin with focus on lifesteal.
	// Create a character like ekko that can transport back in time to previous location (assuming location is empty).

};

