#include "Player.h"
#include "Board.h"

Player::Player(const std::string name, const PlayerNr nr)
	: m_name(PlayerName(name)), m_nr(nr) {

	if (nr == PlayerNr::PLAYER_ONE) {
		const float y = MARGIN - DISTANCE_BEETWEN_POINTS * 2;
		const float x = MARGIN + ((DISTANCE_BEETWEN_POINTS * BOARD_SIZE_X) / 2) + DISTANCE_BEETWEN_POINTS / 2;
		m_name.setPosition(x, y);
	}

	else if (nr == PlayerNr::PLAYER_TWO) {
		const float y = MARGIN + (DISTANCE_BEETWEN_POINTS * BOARD_SIZE_Y) + DISTANCE_BEETWEN_POINTS / 2;
		const float x = MARGIN + ((DISTANCE_BEETWEN_POINTS * BOARD_SIZE_X) / 2) + DISTANCE_BEETWEN_POINTS / 2;
		m_name.setPosition(x, y);
	}
}

sf::Text Player::getText() {
	return m_name.getText();
}

void Player::PlayerTurnStart() {
	m_name.enableUnderline();
}

void Player::PlayerTurnEnd() {
	m_name.disableUnderline();
}