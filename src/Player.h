#pragma once

#include <string>

enum PlayerNr {
	PLAYER_ONE = 1,
	PLAYER_TWO = 2
};

class Player {
private:
	std::string m_name;
	PlayerNr m_nr;
	bool isMovePoint;

public:
	Player() : 
		m_name(""), m_nr(PlayerNr::PLAYER_ONE), isMovePoint(true) {};

	Player(std::string name, PlayerNr nr) : 
		m_name(name), m_nr(nr), isMovePoint(true) {}

	void setName(std::string name) {
		m_name = name;
	}
};