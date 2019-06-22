#pragma once

#include <string>

#include "PlayerName.h"

enum PlayerNr {
	PLAYER_ONE = 1,
	PLAYER_TWO = 2
};

class Player {
private:
	PlayerName m_name;
	PlayerNr m_nr;
	bool isMovePoint;

public:
	Player(const std::string name = "NoName", const PlayerNr nr = PlayerNr::PLAYER_ONE);

	sf::Text getText();
};