#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Ball.h"

#define BOARD_SIZE_X 9
#define BOARD_SIZE_Y 11
#define POINT_RADIUS 5
#define HOVER_POINT_RADIUS POINT_RADIUS * 4
#define DISTANCE_BEETWEN_POINTS 50
#define MARGIN 150
#define GATE_SIZE 2

class Board {
private:
	Point m_points[BOARD_SIZE_X][BOARD_SIZE_Y];
	sf::CircleShape m_hoverPoint;
	sf::ConvexShape m_frame;
	Ball m_ball;
	sf::VertexArray m_lines;

	void initPoints();
	void initFrame();
	void initHoverPoint();
	void initBall();
	void initLines();

	void drawPoints(sf::RenderWindow* hWindow);
	void drawFrame(sf::RenderWindow* hWindow);

	Point* getPoint(const sf::Vector2f pointPos);

public:
	Board();

	void drawBoard(sf::RenderWindow* hWindow);
	sf::Vector2f getPointPosition(const unsigned x, const unsigned y);
	void movingTheBall(const sf::Vector2f newPositionOfBall);
	bool isLineOnPoint(const unsigned x, const unsigned y, const uint8_t direction);
	void toggleHoverPoint(const sf::Vector2f position = sf::Vector2f(-20, -20));
	sf::Vector2f getBallPosition();
	bool isBouncePosibility(const sf::Vector2f point);
};