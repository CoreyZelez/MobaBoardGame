#pragma once

class Character;
struct Position;

class CharacterFactory
{
public:
	Character createBloodlordKlaus(Position initPos, double multiplier);  // Assassin with focus on lifesteal (JGL).
	Character createVoidArcherLeanna(Position initPos, double multiplier);  // Assassin with focus on lifesteal.
	// Create a character like ekko that can transport back in time to previous location (assuming location is empty).

};

