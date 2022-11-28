#pragma once
#include "MapEditor.h"

class MapEditorHandler
{
public:
	MapEditorHandler(MapEditor &editor);

	void handleInput(sf::RenderWindow &window);

private:
	MapEditor &editor;

};

