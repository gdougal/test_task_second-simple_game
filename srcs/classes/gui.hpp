//
// Created by Gilberto Dougal on 4/25/21.
//

#ifndef HELLO_SFML_GUI_HPP
#define HELLO_SFML_GUI_HPP
#include "../shooting_range.hpp"


class gui {
private:
	static sf::Font													font_;
	static sf::Text													score_;
	static sf::Text													time_;
public:
	gui() = delete;
	gui(const gui &ref) = delete;
	gui &operator=(const gui &ref) = delete;
	virtual ~gui() = delete;

	static void		setSettings() {
		font_.loadFromFile("/Library/Fonts/Arial.ttf");

		score_.setFont(font_);
		score_.setCharacterSize(static_cast<unsigned int>(g_win_height)/40);
		score_.setPosition(g_resourses.cannon.origin.y + score_.getCharacterSize(), 200);
		score_.setFillColor(sf::Color(255,255,255));
		score_.setStyle(sf::Text::Bold);
	}

	static void setScore(const std::string& score) { score_.setString(score); }
};


#endif //HELLO_SFML_GUI_HPP
