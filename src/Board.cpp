#pragma once
#include "Board.h"

#pragma region Public

Board::Board() {
	initPoints();
	initHoverPoint();
	initFrame();
	initBall();
	initLines();
}

void Board::drawBoard(sf::RenderWindow* hWindow) {
	drawFrame(hWindow);
	drawPoints(hWindow);

	hWindow->draw(m_lines);

	// it's useless to draw a shape when it has negative coords
	if (m_hoverPoint.getPosition().x != -20)
		hWindow->draw(m_hoverPoint);
}

sf::Vector2f Board::getPointPosition(const unsigned x, const unsigned y) {
	if (BOARD_SIZE_X < x || BOARD_SIZE_Y < y)
		return sf::Vector2f();

	return m_points[x][y].getPosition();
}

void Board::movingTheBall(sf::Vector2f newPositionOfBall) {
	Point* newBall = getPoint(newPositionOfBall);
	m_ball.setNewBall(newBall);

	m_lines.append(sf::Vertex(
		newBall->getPosition(),
		sf::Color::Color(166, 255, 166, 255))
	);
}

bool Board::isLineOnPoint(const unsigned x, const unsigned y, const uint8_t direction) {
	return getPoint(sf::Vector2f(x, y))->isLine(direction);
}

void Board::toggleHoverPoint(const sf::Vector2f position) {
	m_hoverPoint.setPosition(position);
}

sf::Vector2f Board::getBallPosition() {
	return m_ball.getPosition();
}

// If the point has any connections before moving
// the player has additional movement
bool Board::isBouncePosibility(const sf::Vector2f pointPosition) {
	Point* point = getPoint(pointPosition);

	return (point->isAnyConnections() | point->isEdge());
}

#pragma endregion

#pragma region Private
#pragma region Init

void Board::initPoints() {
	sf::CircleShape* tempCirc;
	for (unsigned y = 0; y < BOARD_SIZE_Y; ++y) {
		for (unsigned x = 0; x < BOARD_SIZE_X; x++) {
			tempCirc = &m_points[x][y];

			// Create new points
			if (x == 0 || y == 0 || x == (BOARD_SIZE_X - 1) || y == (BOARD_SIZE_Y - 1))
				m_points[x][y] = Point(POINT_RADIUS, true);
			else
				m_points[x][y] = Point(POINT_RADIUS, false);

			tempCirc->setFillColor(sf::Color::Color(166,255,166,255));

			// set new center
			tempCirc->setOrigin(POINT_RADIUS, POINT_RADIUS);
			tempCirc->setPosition(
				(x * DISTANCE_BEETWEN_POINTS) + MARGIN,
				(y * DISTANCE_BEETWEN_POINTS) + MARGIN
			);
		}
	}
}

// Initialize frame with 12 corners
// it should look like a football pitch
void Board::initFrame() {
	// Some math's magic to have scalable board
	const float GATE_LEFT_CORNER_POINT_X =
		(((BOARD_SIZE_X - 1) / 2) - 1) * DISTANCE_BEETWEN_POINTS + MARGIN;

	const float GATE_RIGHT_CORNER_POINT_X =
		GATE_LEFT_CORNER_POINT_X + DISTANCE_BEETWEN_POINTS * GATE_SIZE;

	const float RIGHT_CORNER_X =
		MARGIN + DISTANCE_BEETWEN_POINTS * (BOARD_SIZE_X - 1);

	const float UPPER_ENDLINE_Y = MARGIN;
	const float UPPER_GATELINE_Y = (MARGIN - DISTANCE_BEETWEN_POINTS);

	const float BOTTOM_ENDlINE_Y =
		MARGIN + DISTANCE_BEETWEN_POINTS * (BOARD_SIZE_Y - 1);

	const float BOTTOM_GATELINE_Y =
		MARGIN + DISTANCE_BEETWEN_POINTS * BOARD_SIZE_Y;


	m_frame = sf::ConvexShape(12);


	// Upper set of corners
	m_frame.setPoint(0, sf::Vector2f(MARGIN, UPPER_ENDLINE_Y));
	m_frame.setPoint(1, sf::Vector2f(GATE_LEFT_CORNER_POINT_X, UPPER_ENDLINE_Y));
	m_frame.setPoint(2, sf::Vector2f(GATE_LEFT_CORNER_POINT_X, UPPER_GATELINE_Y));
	m_frame.setPoint(3, sf::Vector2f(GATE_RIGHT_CORNER_POINT_X, UPPER_GATELINE_Y));
	m_frame.setPoint(4, sf::Vector2f(GATE_RIGHT_CORNER_POINT_X, UPPER_ENDLINE_Y));
	m_frame.setPoint(5, sf::Vector2f(RIGHT_CORNER_X, UPPER_ENDLINE_Y));

	// Bottom set of corners
	m_frame.setPoint(6, sf::Vector2f(RIGHT_CORNER_X, BOTTOM_ENDlINE_Y));
	m_frame.setPoint(7, sf::Vector2f(GATE_RIGHT_CORNER_POINT_X, BOTTOM_ENDlINE_Y));
	m_frame.setPoint(8, sf::Vector2f(GATE_RIGHT_CORNER_POINT_X, BOTTOM_GATELINE_Y));
	m_frame.setPoint(9, sf::Vector2f(GATE_LEFT_CORNER_POINT_X, BOTTOM_GATELINE_Y));
	m_frame.setPoint(10, sf::Vector2f(GATE_LEFT_CORNER_POINT_X, BOTTOM_ENDlINE_Y));
	m_frame.setPoint(11, sf::Vector2f(MARGIN, BOTTOM_ENDlINE_Y));
}

void Board::initHoverPoint() {
	m_hoverPoint = sf::CircleShape(POINT_RADIUS * 2);

	// it should only over-line a point
	m_hoverPoint.setFillColor(sf::Color::Transparent);
	m_hoverPoint.setOutlineColor(sf::Color::Color(238,238,238,220));
	m_hoverPoint.setOutlineThickness(2);

	// set center of the point
	m_hoverPoint.setOrigin(POINT_RADIUS * 2, POINT_RADIUS * 2);

	// at start we don't want to see that circle
	toggleHoverPoint();
}

void Board::initBall() {
	m_ball = Ball(&m_points[(BOARD_SIZE_X - 1) / 2][(BOARD_SIZE_Y - 1) / 2]);
}

void Board::initLines() {
	m_lines = sf::VertexArray(sf::PrimitiveType::LineStrip);

	m_lines.append(sf::Vertex(m_ball.getPosition()));

	m_lines[0].color = sf::Color::Color(166,255,166,255);
}

#pragma endregion
#pragma region Draw

// Draws all points
void Board::drawPoints(sf::RenderWindow* hWindow) {
	for (unsigned y = 0; y < BOARD_SIZE_Y; ++y) {
		for (unsigned x = 0; x < BOARD_SIZE_X; x++) {
			hWindow->draw(m_points[x][y]);
		}
	}
}

// Draws frame around board
void Board::drawFrame(sf::RenderWindow* hWindow) {
	hWindow->draw(m_frame);
	m_frame.setOutlineThickness(5);
	m_frame.setOutlineColor(sf::Color::Color(238, 238, 238, 200));
	m_frame.setFillColor(sf::Color::Color(28,28,28,255));
}

#pragma endregion

Point* Board::getPoint(const sf::Vector2f pointPos) {
	for (unsigned y = 0; y < BOARD_SIZE_Y; ++y) {
		for (unsigned x = 0; x < BOARD_SIZE_X; x++) {
			if (m_points[x][y].getPosition() == pointPos)
				return &m_points[x][y];
		}
	}

	return new Point();
}

#pragma endregion