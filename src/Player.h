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
	bool isMovePoint;

public:
	const PlayerNr m_nr;
	Player(const std::string name = "NoName", const PlayerNr nr = PlayerNr::PLAYER_ONE);

	sf::Text getText();
	void moved();
	void PlayerTurnStart();
	void PlayerTurnEnd();
};