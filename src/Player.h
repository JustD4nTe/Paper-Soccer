#pragma once

#include <string>

#include "PlayerName.h"

enum PlayerNr {
	NONE = 0,
	PLAYER_ONE = 1,
	PLAYER_TWO = 2
};

class Player {
private:
	PlayerName m_name;

public:
	const PlayerNr m_nr;
	Player(const std::string name = "NoName", const PlayerNr nr = PlayerNr::PLAYER_ONE);

	sf::Text getText();
	void PlayerTurnStart();
	void PlayerTurnEnd();
	std::string getName();
};