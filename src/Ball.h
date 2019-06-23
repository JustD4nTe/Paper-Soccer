#pragma once
#include "Point.h"

enum Directions {
	TOP = 0b00000001,
	TOP_RIGHT = 0b00000010,
	RIGHT = 0b00000100,
	DOWN_RIGHT = 0b00001000,
	DOWN = 0b00010000,
	DOWN_LEFT = 0b00100000,
	LEFT = 0b01000000,
	TOP_LEFT = 0b10000000
};

class Ball {
private:
	Point* m_point;
public:
	Ball() {}
	Ball(Point* point) : m_point(point) {}

	sf::Vector2f getPosition();
	bool isLine(const uint8_t direction);
	void setNewBall(Point* newBall);
	bool isOnTheEdge();
	void setGoal(Point* gate);
};