#pragma once
#include <memory>
#include "Team.h"

class Character;
class GameBoard;
struct Position;

class CharacterFactory
{
public:
	std::shared_ptr<Character> createBloodlordKlaus(GameBoard &gameBoard, Team team, double multiplier);  // Assassin with focus on lifesteal (JGL).
	std::shared_ptr<Character> createVoidArcherLeanna(GameBoard &gameBoard, Team team, double multiplier);  // Assassin with focus on lifesteal.
	// Create a character like ekko that can transport back in time to previous location (assuming location is empty).

};

