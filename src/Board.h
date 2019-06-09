#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define BOARD_SIZE_X 9
#define BOARD_SIZE_Y 11
#define POINT_RADIUS 5
#define DISTANCE_BEETWEN_POINTS 50

class Board {
private:
	sf::CircleShape m_points[BOARD_SIZE_X][BOARD_SIZE_Y];
	sf::CircleShape m_hoverPoint;
	sf::ConvexShape m_frame;
	sf::Vector2f m_ballPosition;

	void initPoints();
	void initFrame();
	void initHoverPoint();
	void initBall();

	void drawPoints(sf::RenderWindow* hWindow);
	void drawFrame(sf::RenderWindow* hWindow);

public:
	Board();

	void drawBoard(sf::RenderWindow* hWindow);
	sf::Vector2f getPointPosition(const unsigned x, const unsigned y);

	void toggleHoverPoint(sf::Vector2f pos = sf::Vector2f(-20, -20)) {
		m_hoverPoint.setPosition(pos);
	}

	sf::Vector2f getBallPosition() {
		return m_ballPosition;
	}
};