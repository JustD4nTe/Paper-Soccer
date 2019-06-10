#pragma once

#include "Board.h"

class Game{
private:
	Board m_board;

	sf::Vector2f availableMove(const sf::Vector2i mousePos);

public:
	Game() : m_board(Board()) {};

	void draw(sf::RenderWindow& mWindow);
	void hoverPoint(const sf::Vector2i mousePos);
	void move(const sf::Vector2i mousePos);
};