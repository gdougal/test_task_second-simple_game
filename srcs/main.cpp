#include <iostream>
#include "classes/logic.hpp"

int	game_cycle() {
	logic						game("srcs/config.txt");
	wrap_window			window(game.getResourses().getWinResourse());
	game.setSessionWindow(window.getPubWindow().get());
	while (window.getPubWindow()->isOpen()) {
		sf::Event e;
		while (window.getPubWindow()->pollEvent(e)) {

			switch (e.type) {
				case sf::Event::EventType::Closed:
					window.getPubWindow()->close();
					break;
				case e.KeyPressed:
					if (e.key.code == sf::Keyboard::Q) {
						game.shooting();
					}
					else if (e.key.code == sf::Keyboard::W) {
						game.bomb_shooting();
					}
					else if (e.key.code == sf::Keyboard::Escape) {
						window.getPubWindow()->clear();
					}
			}
		}
		game.update_game_logic();
		window.getPubWindow()->clear();
		game.draw_game_objects();
		window.getPubWindow()->display();
	}
	return 0;
}


int main() {
	srand(time(nullptr));
	game_cycle();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}