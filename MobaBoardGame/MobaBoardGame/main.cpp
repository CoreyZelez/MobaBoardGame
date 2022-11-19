#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "Attributes.h"
#include "HealthPoisonEffect.h"
#include "ParalyseEffect.h"
#include "Character.h"


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
	CombatAttributes ca = {30, 20, 20 };
	ActionAttributes aca = { 3, 2, 2 };
	AbilityAttributes aba = { 20, 10, 10 };
	SpecialAttributes sa = { 0 };
	CharacterAttributes cha = { aca, ha, ca, aba, sa};
	const std::array<const CharacterAttributes, 8> baseAttributes = { cha, cha, cha, cha, cha, cha, cha, cha };
	Position position{ 0, 1 };

	// Abilities


	//Character character1(position, baseAttributes, nullptr);
	//
	//HealthPoisonEffect hpe(10, 10);
	//ParalyseEffect pe(3);
	//
	//std::unique_ptr<Effect<CharacterAttributes>> eff1 = std::make_unique<HealthPoisonEffect>(hpe);
	//std::unique_ptr<Effect<CharacterAttributes>> eff2 = std::make_unique<ParalyseEffect>(pe);
	//
	//character1.printAttributes();
	//character1.update();
	//	
	//character1.addEffect(eff1);
	//character1.addEffect(eff2);
	//
	//for(int i = 0; i < 40; ++i){
	//	character1.printAttributes();
	//	character1.update();
	//}

	////////////
	// END CONSOLE TESTING
	//////

	return 0;
}