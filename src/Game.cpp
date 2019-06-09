#include "Game.h"

void Game::draw(sf::RenderWindow& mWindow) {
	m_board.drawBoard(&mWindow);
}

// Setting an over-line circle around the point, which mouse is touching (mrrr :)) )
void Game::hoverPoint(const sf::Vector2i mousePos) {
	// disable HoverPoint
	m_board.toggleHoverPoint();

	// checks if point is available
	sf::Vector2f point = availableMove(mousePos);

	// nope
	if (point.x == 0 || point.y == 0)
		return;

	// set offset to this point
	// for better displaying
	point.y -= POINT_RADIUS;
	point.x -= POINT_RADIUS;

	m_board.toggleHoverPoint(point);
}

// Trying to move the ball
void Game::move(const sf::Vector2i mousePos) {
	// checks if point is available
	sf::Vector2f point = availableMove(mousePos);

	// nope
	if (point.x == 0 || point.y == 0)
		return;

	m_board.movingTheBall(point);
}

// At first searching which point is under mouse
// then checks if player can move to this point
sf::Vector2f Game::availableMove(const sf::Vector2i mousePos) {
	const sf::Vector2f ballPosition = m_board.getBallPosition();

	// area where player can see available move
	const unsigned up = ballPosition.y - DISTANCE_BEETWEN_POINTS;
	const unsigned down = ballPosition.y + DISTANCE_BEETWEN_POINTS;
	const unsigned left = ballPosition.x - DISTANCE_BEETWEN_POINTS;
	const unsigned right = ballPosition.x + DISTANCE_BEETWEN_POINTS;

	// searching at all points for the one <3
	for (unsigned x = 0; x < BOARD_SIZE_X; x++) {
		for (unsigned y = 0; y < BOARD_SIZE_Y; y++) {
			sf::Vector2f tempPointPos = m_board.getPointPosition(x, y);

			// got (0,0) when we get out of array
			if (tempPointPos.x == 0 && tempPointPos.y == 0)
				continue;

			// player shouldn't see over-line of the ball
			if (tempPointPos == ballPosition)
				continue;

			// is current point into square of available move?
			if ((tempPointPos.x >= left && tempPointPos.x <= right)
				&& (tempPointPos.y >= up && tempPointPos.y <= down)) {

				// some weird math with SFML
				// basically we used circle equation,
				// but SFML did an awful joke to us and with no reason
				// circle position isn't the center, but left-up corner
				// WHY U DO THIS TO ME???
				if (std::pow((mousePos.x - POINT_RADIUS - tempPointPos.x), 2)
					+ std::pow((mousePos.y - POINT_RADIUS - tempPointPos.y), 2)
					<= std::pow((POINT_RADIUS + 2), 3)) {
						
						// return point which is available to the player
						return tempPointPos;
				}
			}
		}
	}

	// unfortunately there's no point under mouse
	// or this point is unavailable to the player
	return sf::Vector2f(0, 0);
}