//
// Created by Gilberto Dougal on 4/23/21.
//

#include "wrap_window.hpp"

wrap_window::wrap_window(): pub_window(new sf::RenderWindow(sf::VideoMode(g_win_width, g_win_height), "Hello SFML (its me)")) {
	pub_window->setFramerateLimit(g_framerate);
	pub_window->setMouseCursorVisible(false);
	pub_window->setMouseCursorGrabbed(true);
	pub_window->setKeyRepeatEnabled(false);
}

const std::shared_ptr<sf::RenderWindow> &wrap_window::getPubWindow() const {return pub_window;}

