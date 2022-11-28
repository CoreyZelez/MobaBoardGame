#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include "Attributes.h"
#include "Character.h"
#include "CharacterFactory.h"
#include "GameSquare.h"
#include "GameBoard.h"
#include "MapEditor.h"
#include "MapEditorHandler.h"


const int WINDOW_WIDTH = 1920; //1920;
const int WINDOW_HEIGHT = 1080; //1080;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!", sf::Style::Default);
	window.setFramerateLimit(200);
	window.setVerticalSyncEnabled(false);
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	// Camera move data.
	sf::Vector2f oldPos;
	bool moving = false;
	float zoom = 1;

	MapEditor editor(121, 51);
	MapEditorHandler handler(editor);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				// Mouse button is pressed, get the position and set moving as active
				if(event.mouseButton.button == 0) {
					moving = true;
					oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				}
				break;
			case  sf::Event::MouseButtonReleased:
				// Mouse button is released, no longer move
				if(event.mouseButton.button == 0) {
					moving = false;
				}
				break;
			case sf::Event::MouseMoved:
			{
				// Ignore mouse movement unless a button is pressed (see above)
				if(!moving)
					break;
				// Determine the new position in world coordinates
				const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				// Determine how the cursor has moved
				// Swap these to invert the movement direction
				const sf::Vector2f deltaPos = oldPos - newPos;

				// Move our view accordingly and update the window
				view.setCenter(view.getCenter() + deltaPos);
				window.setView(view);

				// Save the new position as the old one
				// We're recalculating this, since we've changed the view
				oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				break;
			}
			case sf::Event::MouseWheelScrolled:
				// Ignore the mouse wheel unless we're not moving
				if(moving)
					break;

				// Determine the scroll direction and adjust the zoom level
				// Again, you can swap these to invert the direction
				if(event.mouseWheelScroll.delta <= -1)
				{
					zoom = std::min(10.f, zoom + .2f);
				}
				else if(event.mouseWheelScroll.delta >= 1)
				{
					zoom = std::max(.5f, zoom - .2f);
				}

				// Update our view
				view.setSize(window.getDefaultView().getSize()); // Reset the size
				view.zoom(zoom); // Apply the zoom level (this transforms the view)
				window.setView(view);
				break;
			}
		}


		window.setView(view);
		window.clear();

		editor.draw(window);
		handler.handleInput(window);

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

	for(int i = 0; i < 14; ++i)
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