#include <SFML/Graphics.hpp>


const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!", sf::Style::Fullscreen);
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

	return 0;
}