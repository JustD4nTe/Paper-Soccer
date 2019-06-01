#pragma once
#include "Board.h"

#define DISTANCE_BEETWEN_POINTS 50.0
#define POINT_RADIUS 5
#define MARGIN 50

#pragma region Public

Board::Board() {
	initPoints();
}

#pragma endregion

#pragma region Private

void Board::initPoints() {
	// Temporary variable
	sf::CircleShape* tempCirc;
	for (unsigned y = 0; y < BOARD_SIZE_Y; ++y) {
		for (unsigned x = 0; x < BOARD_SIZE_X; x++) {
			tempCirc = &m_points[x][y];

			// Create new point
			*tempCirc = sf::CircleShape(POINT_RADIUS);
			tempCirc->setFillColor(sf::Color::Green);
			tempCirc->setPosition((x * DISTANCE_BEETWEN_POINTS) + MARGIN, (y * DISTANCE_BEETWEN_POINTS) + MARGIN);
		}
	}
}

#pragma endregion