#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "Player.h"

class Gate : public sf::CircleShape {
private:
	PlayerNr m_player;

public:
	Gate() {}
	Gate(unsigned point, PlayerNr player)
		: sf::CircleShape(point), m_player(player) {};
};