#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define BOARD_SIZE_X 8
#define BOARD_SIZE_Y 10

class Board {
private:
	sf::CircleShape m_points[BOARD_SIZE_X][BOARD_SIZE_Y];

	void initPoints();

public:
	Board();
};