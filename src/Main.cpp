#include <SFML/Graphics.hpp>

#include "Game.h"

#define WINDOW_RES_X 1024
#define WINDOW_RES_Y 800

int main() {
	sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_RES_X, WINDOW_RES_Y), "Paper-Soccer");

	Game game = Game();

	while (mainWindow.isOpen()) {
		sf::Event event;
		while (mainWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				mainWindow.close();

			if (event.key.code == sf::Mouse::Left) {
				game.move(sf::Mouse::getPosition(mainWindow));
			}
		}

		game.hoverPoint(sf::Mouse::getPosition(mainWindow));

		game.draw(mainWindow);

		if (game.isEnd())
			break;
	}

	return 0;
}