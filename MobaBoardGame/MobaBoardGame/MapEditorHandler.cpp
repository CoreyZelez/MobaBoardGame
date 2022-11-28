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
}
