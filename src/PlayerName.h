#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class PlayerName {
private:
	sf::Font m_font;
	sf::Text m_nameToDisplay;
	std::string m_name;

public:
	PlayerName(const std::string name = "NoName");

	sf::Text getText();
	void setPosition(const float x, const float y);
	void enableUnderline();
	void disableUnderline();
};