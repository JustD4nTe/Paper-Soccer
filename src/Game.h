#pragma once

#include "Board.h"

class Game{
private:
	Board m_board;

public:
	Game() : m_board(Board()) {};

	void draw(sf::RenderWindow& mWindow);
	void hoverPoint(const sf::Vector2i mousePos);
};