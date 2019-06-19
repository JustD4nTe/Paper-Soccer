#pragma once

#include "Board.h"
#include "Player.h"

class Game{
private:
	Board m_board;
	Player* m_players[2];

	sf::Vector2f availableMove(const sf::Vector2i mousePos);
	bool isAnyLineBetweenPoints(const sf::Vector2f ballPos, const sf::Vector2f pointPo);


public:
	Game();

	void draw(sf::RenderWindow& mWindow);
	void hoverPoint(const sf::Vector2i mousePos);
	void move(const sf::Vector2i mousePos);
};