#include <SFML/Graphics.hpp>

#include "Board.h"

#define WINDOW_RES_X 1024
#define WINDOW_RES_Y 800

int main(){
	sf::RenderWindow window(sf::VideoMode(WINDOW_RES_X, WINDOW_RES_Y), "Paper-Soccer");

	Board board = Board();

	while (window.isOpen())	{
		sf::Event event;
		while (window.pollEvent(event))		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		board.drawBoard(&window);
		window.display();
	}

	return 0;
}