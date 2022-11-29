#include "MapEditorHandler.h"

MapEditorHandler::MapEditorHandler(MapEditor &editor)
	: editor(editor)
{
}

void MapEditorHandler::handleInput(sf::RenderWindow &window)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		editor.changeSquare(worldPos.x, worldPos.y);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		editor.setCurrentType(impassableForest);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		editor.setCurrentType(deepWater);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		editor.setCurrentType(mountain);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		editor.setCurrentType(lava);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		editor.setCurrentType(grass);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		editor.setCurrentType(mountainFloor);
	}
}
