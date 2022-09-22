#include "Map.h"

Map::Map(string name)
{
	texture.loadFromFile("maps/" + name + "/" + name + ".png");
	sprite.setTexture(texture);

}

void Map::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}
