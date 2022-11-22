#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "Attributes.h"
#include "Character.h"
#include "AttackHealPassive.h"
#include "LifeHarvestAbility.h"


const int WINDOW_WIDTH = 1280; //1920;
const int WINDOW_HEIGHT = 720; //1080;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!", sf::Style::Default);
	window.setFramerateLimit(60);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.display();
	}

	////////////
	// CONSOLE TESTING
	//////
	
	// Attributes
	HealthAttributes ha = { 300, 200 };
	CombatAttributes ca = {30, 20, 15, 10 };
	ActionAttributes aca = { 3, 2, 2, 1, 2, 3 };
	AbilityAttributes aba = { 20, 10, 10 };
	CharacterAttributes cha = { aca, ha, ca, aba};
	const std::array<const CharacterAttributes, 8> baseAttributes = { cha, cha, cha, cha, cha, cha, cha, cha };
	Position pos1{ 0, 1 };
	Position pos2{ 1, 3 };

	// abilities
	AbilityArsenal arsenal = { &AttackHealPassive(), 
		&LifeHarvestAbility({50, 100, 150}, 2, 0.5), 
		&LifeHarvestAbility({100, 160, 240}, 4, 0.3) };

	// Characters
	Character character1(pos1, baseAttributes, arsenal);
	Character character2(pos2, baseAttributes, arsenal);

	character1.basicAttack(character2);
	character1.printAttributes();
	character2.printAttributes();

	////////////
	// END CONSOLE TESTING
	//////

	return 0;
}