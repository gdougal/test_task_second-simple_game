//
// Created by Gilberto Dougal on 4/23/21.
//

#include "wrap_window.hpp"

wrap_window::wrap_window(const win_resource& config): pub_window(new sf::RenderWindow(sf::VideoMode(config.getWinWidthUint(), config.getWinHeightUint()), "Hello SFML (its me)")) {
	pub_window->setFramerateLimit(config.getFramerateUint());
	pub_window->setMouseCursorVisible(config.isMouseCursorVisible());
	pub_window->setMouseCursorGrabbed(config.isMouseCursorGrabbed());
	pub_window->setKeyRepeatEnabled(config.isKeyRepeatEnabled());
}

const std::shared_ptr<sf::RenderWindow> &wrap_window::getPubWindow() const {
	return pub_window;
}

