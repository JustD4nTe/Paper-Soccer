#include <SFML/Graphics.hpp>

#include "Game.h"

#define WINDOW_RES_X 1024
#define WINDOW_RES_Y 800

int main() {
	sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_RES_X, WINDOW_RES_Y), "Paper-Soccer",
		sf::Style::Titlebar | sf::Style::Close);

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

	if (game.isEnd()) {
		std::string string = game.getWinner();

		const unsigned fontSize = 50;
		const unsigned x = string.length() * (fontSize/2);

		sf::RenderWindow endWindow(sf::VideoMode(x, fontSize + 5), "End", sf::Style::None);

		sf::Font font = sf::Font();
		sf::Text text = sf::Text();
		if (font.loadFromFile("robotomono.ttf")) {
			text.setFont(font);
			text.setString(string);
			text.setCharacterSize(fontSize);
			text.setFillColor(sf::Color::White);
		}
		while (endWindow.isOpen()) {
			sf::Event event;
			while (endWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
					endWindow.close();
					mainWindow.close();
				}
			}
			while (mainWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
					mainWindow.close();
					endWindow.close();
				}
			}
			endWindow.clear();
			endWindow.draw(text);
			endWindow.display();
		}
	}

	return 0;
}