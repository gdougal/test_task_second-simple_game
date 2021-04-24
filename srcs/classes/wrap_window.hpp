//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_WRAP_WINDOW_HPP
#define HELLO_SFML_WRAP_WINDOW_HPP
#include "../shooting_range.hpp"
#include <memory>

class wrap_window {
private:
	std::shared_ptr<sf::RenderWindow>	pub_window;
public:
	wrap_window();
	wrap_window(const wrap_window &ref) = default;
	wrap_window &operator=(const wrap_window &ref) = default;

	const std::shared_ptr<sf::RenderWindow> &getPubWindow() const;

	~wrap_window() {};
};


#endif //HELLO_SFML_WRAP_WINDOW_HPP
