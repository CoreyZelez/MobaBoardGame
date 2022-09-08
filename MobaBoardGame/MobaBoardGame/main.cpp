#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "Character.h"
#include "Attributes.h"
#include "HealthPoisonEffect.h"


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

	HealthAttributes ha = { 300, 200 };
	CombatAttributes ca = {30, 20, 20 };
	ActionAttributes aca = { 3, 2, 2 };
	AbilityAttributes aba = { 20, 10, 10 };
	CharacterAttributes cha = { aca, ha, ca, aba};
	const std::array<const CharacterAttributes, 8> baseAttributes = { cha, cha, cha, cha, cha, cha, cha, cha };
	Character character1(baseAttributes);

	character1.printAttributes();
	HealthPoisonEffect hpe(10, 10);
	std::unique_ptr<Effect<CharacterAttributes>> eff = std::make_unique<HealthPoisonEffect>(hpe);

	character1.addEffect(eff);

	for(int i = 0; i < 40; ++i){
		character1.update();
		character1.printAttributes();
	}

	////////////
	// END CONSOLE TESTING
	//////

	return 0;
}