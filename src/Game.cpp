#include "Game.h"

void Game::draw(sf::RenderWindow& mWindow) {
	m_board.drawBoard(&mWindow);
}
