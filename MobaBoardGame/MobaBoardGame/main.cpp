#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include "Attributes.h"
#include "Character.h"
#include "CharacterFactory.h"


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

	CharacterFactory factory;

	Character character1 = factory.createVoidArcherLeanna({ 2,2 }, 1);
	Character character2 = factory.createBloodlordKlaus({1,1}, 1);

	character1.init();
	character2.init();

	character1.printAttributes();
	character2.printAttributes();

	for(int i = 0; i < 13; ++i)
	{
		// leanna
		character1.basicAttack(character2);

		character1.update();
		character2.update();

		// klaus
		character2.basicAttack(character1);

		character1.update();
		character2.update();
	}

	character1.printAttributes();
	character2.printAttributes();

	character2.useAbility2(character2);
	character2.basicAttack(character1);

	character1.update();
	character2.update();

	character1.printAttributes();
	character2.printAttributes();




	////////////
	// END CONSOLE TESTING
	//////

	return 0;
}