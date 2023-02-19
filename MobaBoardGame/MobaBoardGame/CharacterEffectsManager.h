#pragma once
#include <list>
#include <memory>
#include "EffectsManager.h"

class Character;

class CharacterEffectsManager : public EffectsManager<Character>
{
public:
	CharacterEffectsManager(Character &character);

	void update();  // Calls update on each effect.

private:

};

