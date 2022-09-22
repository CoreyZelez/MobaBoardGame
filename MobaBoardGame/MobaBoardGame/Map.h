#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Map
{
public:
	Map(string name);

	void draw(sf::RenderWindow &window);

private:
	Texture texture;
	Sprite sprite;
};

