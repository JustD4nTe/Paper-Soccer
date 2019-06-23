#include "PlayerName.h"

PlayerName::PlayerName(const std::string name) : m_name(name) {
	if (m_font.loadFromFile("robotomono.ttf")) {
		m_nameToDisplay.setFont(m_font);
		m_nameToDisplay.setString(m_name);
		m_nameToDisplay.setCharacterSize(24);
		m_nameToDisplay.setFillColor(sf::Color::Color(238,238,238,255));
		m_nameToDisplay.setOrigin((m_name.length() * 24) / 2, 0);
	}

	else {
		//display error about missing font file
	}
}

sf::Text PlayerName::getText() {
	return m_nameToDisplay;
}

void PlayerName::setPosition(const float x, const float y) {
	m_nameToDisplay.setPosition(x, y);
}

void PlayerName::enableUnderline() {
	m_nameToDisplay.setStyle(sf::Text::Underlined);
}

void PlayerName::disableUnderline() {
	m_nameToDisplay.setStyle(sf::Text::Regular);
}