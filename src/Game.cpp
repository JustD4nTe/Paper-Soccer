#include "Game.h"

Game::Game() : m_board(Board()) {
	m_players[0] = new Player("Player 1", PlayerNr::PLAYER_ONE);
	m_players[1] = new Player("Player 2", PlayerNr::PLAYER_TWO);

	m_currentPlayer = m_players[0];
	m_currentPlayer->PlayerTurnStart();

	m_isEnd = false;
}

void Game::draw(sf::RenderWindow& mWindow) {
	mWindow.clear();

	m_board.drawBoard(&mWindow);
	drawPlayers(&mWindow);

	mWindow.display();
}

// Setting an over-line circle around the point, which mouse is touching (mrrr :)) )
void Game::hoverPoint(const sf::Vector2i mousePos) {
	// disable HoverPoint
	m_board.toggleHoverPoint();

	// checks if point is available
	sf::Vector2f point = getPointUnderMouse(mousePos);

	// nope
	if (point.x == 0 || point.y == 0)
		return;

	m_board.toggleHoverPoint(point);
}

// Trying to move the ball
void Game::move(const sf::Vector2i mousePos) {
	// checks if point is available
	sf::Vector2f point = getPointUnderMouse(mousePos);

	// nope
	if (point.x == 0 || point.y == 0)
		return;


	// checking if there is any connections with future ball position
	const bool isPlayerShouldNotEndTurn = m_board.isBouncePosibility(point);

	// change position of ball
	m_isEnd = m_board.movingTheBall(point);

	if(m_isEnd)
		isOwnGoal();

	// if there aren't any moves
	// game is over
	if(!m_isEnd)
		m_isEnd = !isAvailableMoves();

	// if there isn't any connections player's turn is end
	if (!isPlayerShouldNotEndTurn && !m_isEnd) {
		
		// end turn
		m_currentPlayer->PlayerTurnEnd();

		changePlayer();

		// start new turn
		m_currentPlayer->PlayerTurnStart();
	}
}

// At first searching which point is under mouse
// then checks if player can move to this point
sf::Vector2f Game::getPointUnderMouse(const sf::Vector2i mousePos) {
	const sf::Vector2f ballPosition = m_board.getBallPosition();
	const bool isBallOnTheEdge = m_board.isBallOnTheEdge();

	// area where player can see available move
	const float up = ballPosition.y - DISTANCE_BEETWEN_POINTS;
	const float down = ballPosition.y + DISTANCE_BEETWEN_POINTS;
	const float left = ballPosition.x - DISTANCE_BEETWEN_POINTS;
	const float right = ballPosition.x + DISTANCE_BEETWEN_POINTS;

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
			bool isInSquare = (tempPointPos.x >= left && tempPointPos.x <= right)
				&& (tempPointPos.y >= up && tempPointPos.y <= down);


			// player shouldn't move on the edge of football pitch
			bool isNotEdgeBetweenBallAndPoint = !(isBallOnTheEdge & m_board.isPointOnTheEdge(x,y));


			if (isInSquare && isNotEdgeBetweenBallAndPoint
				&& !isAnyLineBetweenPoints(ballPosition, tempPointPos)) {
				// We used circle equation 
				// to check mouse position with current point
				if (std::pow((mousePos.x - tempPointPos.x), 2)
					+ std::pow((mousePos.y - tempPointPos.y), 2)
					<= std::pow(HOVER_POINT_RADIUS, 2)) {

					// return point which is available to the player
					return tempPointPos;

				}
			}
		}
	}

	// when we didn't find the one in points
	// we have to search in gates
	for (unsigned i = 0; i < 6; i++) {
		sf::Vector2f tempGatePos = m_board.getGatePosition(i);
		
		if ((tempGatePos.x >= left && tempGatePos.x <= right)
			&& (tempGatePos.y >= up && tempGatePos.y <= down)) {
			// We used circle equation 
			// to check mouse position with current point
			if (std::pow((mousePos.x - tempGatePos.x), 2)
				+ std::pow((mousePos.y - tempGatePos.y), 2)
				<= std::pow(HOVER_POINT_RADIUS, 2)) {

				// return point which is available to the player
				return tempGatePos;
			}
		}
	}


	// unfortunately there's no point under mouse
	// or this point is unavailable to the player
	return sf::Vector2f(0, 0);
}

bool Game::isAnyLineBetweenPoints(const sf::Vector2f ballPos, const sf::Vector2f pointPos) {
	if (ballPos.x == pointPos.x) {
		if (ballPos.y > pointPos.y) {
			return (m_board.isLineOnPoint(ballPos.x, ballPos.y, Directions::TOP)
				&& m_board.isLineOnPoint(pointPos.x, pointPos.y, Directions::DOWN));
		}

		else if (ballPos.y < pointPos.y) {
			return (m_board.isLineOnPoint(ballPos.x, ballPos.y, Directions::DOWN)
				&& m_board.isLineOnPoint(pointPos.x, pointPos.y, Directions::TOP));
		}
	}

	else if (ballPos.y == pointPos.y) {
		if (ballPos.x > pointPos.x) {
			return (m_board.isLineOnPoint(ballPos.x, ballPos.y, Directions::LEFT)
				&& m_board.isLineOnPoint(pointPos.x, pointPos.y, Directions::RIGHT));
		}

		else if (ballPos.x < pointPos.x) {
			return (m_board.isLineOnPoint(ballPos.x, ballPos.y, Directions::RIGHT)
				&& m_board.isLineOnPoint(pointPos.x, pointPos.y, Directions::LEFT));
		}
	}

	else if (ballPos.x > pointPos.x) {
		if (ballPos.y > pointPos.y) {
			return (m_board.isLineOnPoint(ballPos.x, ballPos.y, Directions::TOP_LEFT)
				&& m_board.isLineOnPoint(pointPos.x, pointPos.y, Directions::DOWN_RIGHT));
		}

		else if (ballPos.y < pointPos.y) {
			return (m_board.isLineOnPoint(ballPos.x, ballPos.y, Directions::DOWN_LEFT)
				&& m_board.isLineOnPoint(pointPos.x, pointPos.y, Directions::TOP_RIGHT));
		}
	}

	else if (ballPos.x < pointPos.x) {
		if (ballPos.y > pointPos.y) {
			return (m_board.isLineOnPoint(ballPos.x, ballPos.y, Directions::TOP_RIGHT)
				&& m_board.isLineOnPoint(pointPos.x, pointPos.y, Directions::DOWN_LEFT));
		}

		else if (ballPos.y < pointPos.y) {
			return (m_board.isLineOnPoint(ballPos.x, ballPos.y, Directions::DOWN_RIGHT)
				&& m_board.isLineOnPoint(pointPos.x, pointPos.y, Directions::TOP_LEFT));
		}
	}
	return false;
}

// Draw players' name
void Game::drawPlayers(sf::RenderWindow* mWindow) {
	for (Player* player : m_players) {
		mWindow->draw(player->getText());
	}
}

bool Game::isEnd() {
	return m_isEnd;
}

std::string Game::getWinner() {
	return m_currentPlayer->getName() + " won!";
}

// If player 1 shot ball into his gate player 2 won
// not player 1, so we need to change player
void Game::isOwnGoal() {
	if (m_board.whoseGate() == m_currentPlayer->m_nr) {
		changePlayer();
	}
}

bool Game::isAvailableMoves() {
	const sf::Vector2f ballPosition = m_board.getBallPosition();
	const bool isBallOnTheEdge = m_board.isBallOnTheEdge();

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
			bool isInSquare = (tempPointPos.x >= left && tempPointPos.x <= right)
				&& (tempPointPos.y >= up && tempPointPos.y <= down);


			// player shouldn't move on the edge of football pitch
			bool isNotEdgeBetweenBallAndPoint = !(isBallOnTheEdge & m_board.isPointOnTheEdge(x, y));


			if (isInSquare && isNotEdgeBetweenBallAndPoint
				&& !isAnyLineBetweenPoints(ballPosition, tempPointPos)) {
				return true;
			}
		}
	}

	// when we didn't find the one in points
	// we have to search in gates
	for (unsigned i = 0; i < 6; i++) {
		sf::Vector2f tempGatePos = m_board.getGatePosition(i);

		if ((tempGatePos.x >= left && tempGatePos.x <= right)
			&& (tempGatePos.y >= up && tempGatePos.y <= down)) {
				return true;
		}
	}

	changePlayer();

	return false;
}

void Game::changePlayer() {
	if (m_currentPlayer->m_nr == PLAYER_ONE)
		m_currentPlayer = m_players[1];
	else
		m_currentPlayer = m_players[0];
}