#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Ball.h"
#include "Gate.h"

#define BOARD_SIZE_X 9
#define BOARD_SIZE_Y 11
#define POINT_RADIUS 3
#define HOVER_POINT_RADIUS POINT_RADIUS * 4
#define DISTANCE_BEETWEN_POINTS 50
#define MARGIN 150
#define GATE_SIZE 2

class Board {
private:
	Point m_points[BOARD_SIZE_X][BOARD_SIZE_Y];
	// The gate has three points
	// multiply by twice because two players are playing
	Gate m_gates[(GATE_SIZE + 1) * 2];
	sf::CircleShape m_hoverPoint;
	sf::ConvexShape m_frame;
	Ball m_ball;
	sf::VertexArray m_lines;

	void initPoints();
	void initFrame();
	void initHoverPoint();
	void initBall();
	void initLines();
	void initGates();

	void drawPoints(sf::RenderWindow* hWindow);
	void drawFrame(sf::RenderWindow* hWindow);
	void drawGates(sf::RenderWindow* hWindow);

	Point* getPoint(const sf::Vector2f pointPos);
	Gate* getGate(const sf::Vector2f gatePos);

public:
	Board();

	void drawBoard(sf::RenderWindow* hWindow);
	sf::Vector2f getPointPosition(const unsigned x, const unsigned y);
	sf::Vector2f getGatePosition(const unsigned iterator);
	bool movingTheBall(const sf::Vector2f newPositionOfBall);
	bool isLineOnPoint(const float x, const float y, const uint8_t direction);
	void toggleHoverPoint(const sf::Vector2f position = sf::Vector2f(-20, -20));
	sf::Vector2f getBallPosition();
	bool isBouncePosibility(const sf::Vector2f point);
	bool isBallOnTheEdge();
	bool isPointOnTheEdge(const unsigned x, const unsigned y);
	PlayerNr whoseGate();
};