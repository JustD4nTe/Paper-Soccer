#pragma once

#include "Board.h"
#include "Player.h"

class Game {
private:
	Board m_board;
	Player* m_players[2];
	Player* m_currentPlayer;
	bool m_isEnd;

	sf::Vector2f getPointUnderMouse(const sf::Vector2i mousePos);
	bool isAnyLineBetweenPoints(const sf::Vector2f ballPos, const sf::Vector2f pointPo);
	void drawPlayers(sf::RenderWindow* mWindow);
	void isOwnGoal();
	bool isAvailableMoves();
	void changePlayer();

public:
	Game();

	void draw(sf::RenderWindow& mWindow);
	void hoverPoint(const sf::Vector2i mousePos);
	void move(const sf::Vector2i mousePos);
	bool isEnd();
	std::string getWinner();
};