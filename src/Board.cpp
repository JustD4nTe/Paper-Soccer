#pragma once
#include "Board.h"

#define DISTANCE_BEETWEN_POINTS 50
#define MARGIN 100
#define GATE_SIZE 2

#pragma region Public

Board::Board() {
	initPoints();
	initHoverPoint();
	initFrame();
}

void Board::drawBoard(sf::RenderWindow* hWindow) {
	drawFrame(hWindow);
	drawPoints(hWindow);
		
	// it useless to draw o shape when it have a negative coords
	if (m_hoverPoint.getPosition().x != -20)
		hWindow->draw(m_hoverPoint);
}

sf::Vector2f Board::getPointPosition(const unsigned x, const unsigned y) {
	if (BOARD_SIZE_X < x || BOARD_SIZE_Y < y)
		return sf::Vector2f();

	return m_points[x][y].getPosition();
}

#pragma endregion

#pragma region Private

void Board::initPoints() {
	sf::CircleShape* tempCirc;
	for (unsigned y = 0; y < BOARD_SIZE_Y; ++y) {
		for (unsigned x = 0; x < BOARD_SIZE_X; x++) {
			tempCirc = &m_points[x][y];

			// Create new point
			*tempCirc = sf::CircleShape(POINT_RADIUS);
			tempCirc->setFillColor(sf::Color::Green);
			tempCirc->setPosition(
				(x * DISTANCE_BEETWEN_POINTS) + MARGIN,
				(y * DISTANCE_BEETWEN_POINTS) + MARGIN
			);
		}
	}
}

// Initialize frame with 12 corners
// it should looks like a football pitch
void Board::initFrame() {
	// Some math's magic to have scalable board
	const float GATE_LEFT_CORNER_POINT_X =
		(((BOARD_SIZE_X - 1) / 2) - 1) * DISTANCE_BEETWEN_POINTS + MARGIN + POINT_RADIUS;

	const float GATE_RIGHT_CORNER_POINT_X = 
		GATE_LEFT_CORNER_POINT_X + DISTANCE_BEETWEN_POINTS * GATE_SIZE;

	const float RIGHT_CORNER_X = 
		MARGIN + POINT_RADIUS + DISTANCE_BEETWEN_POINTS * (BOARD_SIZE_X - 1);

	const float UPPER_ENDLINE_Y = MARGIN + POINT_RADIUS;
	const float UPPER_GATELINE_Y = (MARGIN - DISTANCE_BEETWEN_POINTS) + POINT_RADIUS;

	const float BOTTOM_ENDlINE_Y =
		MARGIN + POINT_RADIUS + DISTANCE_BEETWEN_POINTS * (BOARD_SIZE_Y - 1);

	const float BOTTOM_GATELINE_Y = 
		MARGIN + POINT_RADIUS + DISTANCE_BEETWEN_POINTS * BOARD_SIZE_Y;


	m_frame = sf::ConvexShape(12);


	// Upper set of corners
	m_frame.setPoint(0, sf::Vector2f(MARGIN + POINT_RADIUS, UPPER_ENDLINE_Y));
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
	m_frame.setPoint(11, sf::Vector2f(MARGIN + POINT_RADIUS, BOTTOM_ENDlINE_Y));
}

void Board::initHoverPoint() {
	m_hoverPoint = sf::CircleShape(POINT_RADIUS * 2);

	// it should only over-line a point
	m_hoverPoint.setFillColor(sf::Color::Transparent);
	m_hoverPoint.setOutlineColor(sf::Color::Magenta);
	m_hoverPoint.setOutlineThickness(2);

	// at start we don't want to see that circle
	toggleHoverPoint();
}

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
}

#pragma endregion