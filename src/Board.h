#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define BOARD_SIZE_X 9
#define BOARD_SIZE_Y 11

class Board {
private:
	sf::CircleShape m_points[BOARD_SIZE_X][BOARD_SIZE_Y];
	sf::ConvexShape m_frame;

	void initPoints();
	void initFrame();

	void drawPoints(sf::RenderWindow* hWindow);
	void drawFrame(sf::RenderWindow* hWindow);

public:
	Board();

	void drawBoard(sf::RenderWindow* hWindow);
};