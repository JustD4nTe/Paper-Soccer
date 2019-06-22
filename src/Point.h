#pragma once
#include <SFML/Graphics/CircleShape.hpp>

class Point : public sf::CircleShape {
private:
	uint8_t m_lines = 0b00000000;
public:
	Point(){};
	Point(const unsigned point) : sf::CircleShape(point){};

	void newLine(const uint8_t direction) {
		m_lines |= direction;
	}

	bool isLine(const uint8_t direction) {
		return (m_lines & direction);
	}

	// Is any connections with this point
	bool isAnyConnections() {
		return m_lines > 0 ? true : false;
	}
};