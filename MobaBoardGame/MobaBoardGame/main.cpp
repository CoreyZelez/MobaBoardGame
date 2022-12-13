#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include "EntityAttributes.h"
#include "Character.h"
#include "CharacterFactory.h"
#include "GameSquare.h"
#include "GameBoard.h"
#include "MapEditor.h"
#include "MapEditorHandler.h"
#include "Game.h"
#include "GameHandler.h"



const int WINDOW_WIDTH = 1920; //1920;
const int WINDOW_HEIGHT = 1080; //1080;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!", sf::Style::Default);
	window.setFramerateLimit(200);
	window.setVerticalSyncEnabled(false);
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));


	const bool editorMode = true;

	// Game data.
	Game game;
	GameHandler gameHandler(game);

	// Editor data.
	MapEditor editor(101, 72);
	MapEditorHandler editorHandler(editor);
	editor.importMap("map V1");

	// Camera move data.
	sf::Vector2f oldPos;
	bool moving = false;
	float zoom = 1;

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

		// Draw and update game/editor.

		window.setView(view);
		window.clear();

		if(editorMode)
		{
			editor.draw(window);
			editorHandler.handleInput(window);
		}
		else
		{
			game.draw(window);
			gameHandler.handleInput(window);
			game.update();
		}

		window.display();
	}

	if(editorMode)
	{
		editor.exportMap("map V1");
	}


	////////////
	// CONSOLE TESTING
	//////



	////////////
	// END CONSOLE TESTING
	//////

	return 0;
}