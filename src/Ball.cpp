#pragma once
#include "Ball.h"

sf::Vector2f Ball::getPosition() {
	return m_point->getPosition();
}

bool Ball::isLine(const uint8_t direction) {
	return m_point->isLine(direction);
}

void Ball::setNewBall(Point* newBall) {
	sf::Vector2f oldBallPosition = m_point->getPosition();
	sf::Vector2f newBallPosition = newBall->getPosition();

	if (oldBallPosition.x == newBallPosition.x) {
		if (oldBallPosition.y > newBallPosition.y) {
			m_point->newLine(Directions::TOP);
			newBall->newLine(Directions::DOWN);
		}

		else if (oldBallPosition.y < newBallPosition.y) {
			m_point->newLine(Directions::DOWN);
			newBall->newLine(Directions::TOP);
		}
	}

	else if (oldBallPosition.y == newBallPosition.y) {
		if (oldBallPosition.x > newBallPosition.x) {
			m_point->newLine(Directions::LEFT);
			newBall->newLine(Directions::RIGHT);
		}

		else if (oldBallPosition.x < newBallPosition.x) {
			m_point->newLine(Directions::RIGHT);
			newBall->newLine(Directions::LEFT);
		}
	}

	else if (oldBallPosition.x > newBallPosition.x) {
		if (oldBallPosition.y > newBallPosition.y) {
			m_point->newLine(Directions::TOP_LEFT);
			newBall->newLine(Directions::DOWN_RIGHT);
		}

		else if (oldBallPosition.y < newBallPosition.y) {
			m_point->newLine(Directions::DOWN_LEFT);
			newBall->newLine(Directions::TOP_RIGHT);
		}
	}

	else if (oldBallPosition.x < newBallPosition.x) {
		if (oldBallPosition.y > newBallPosition.y) {
			m_point->newLine(Directions::TOP_RIGHT);
			newBall->newLine(Directions::DOWN_LEFT);
		}

		else if (oldBallPosition.y < newBallPosition.y) {
			m_point->newLine(Directions::DOWN_RIGHT);
			newBall->newLine(Directions::TOP_LEFT);
		}
	}

	m_point = newBall;
}

bool Ball::isOnTheEdge() {
	return m_point->isEdge();
}

void Ball::setGoal(Point* gate) {
	m_point = gate;
}