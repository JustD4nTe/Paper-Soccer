#include "Game.h"

void Game::draw(sf::RenderWindow& mWindow) {
	m_board.drawBoard(&mWindow);
}

// Setting an over-line circle around the point, which mouse is touching (mrrr :)) )
void Game::hoverPoint(const sf::Vector2i mousePos) {
	m_board.toggleHoverPoint();

	for (unsigned x = 0; x < BOARD_SIZE_X; x++) {
		for (unsigned y = 0; y < BOARD_SIZE_Y; y++) {
			sf::Vector2f tempPointPos = m_board.getPointPosition(x, y);

			// got (0,0) when we get out of array
			if (tempPointPos.x == 0 && tempPointPos.y == 0)
				continue;




			// some weird math with SFML
			// basically we used circle equation,
			// but SFML did an awful joke to us and with no reason
			// circle position isn't the center, but left-up corner
			// WHY U DO THIS TO ME???
			if (std::pow((mousePos.x - POINT_RADIUS - tempPointPos.x), 2)
				+ std::pow((mousePos.y - POINT_RADIUS - tempPointPos.y), 2)
				<= std::pow((POINT_RADIUS + 2), 3)) {

					sf::Vector2f newHoverPointPos =	sf::Vector2f(
						tempPointPos.x - POINT_RADIUS, 
						tempPointPos.y - POINT_RADIUS
					);

					m_board.toggleHoverPoint(newHoverPointPos);
			}
		}
	}
}