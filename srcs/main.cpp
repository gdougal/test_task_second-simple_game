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
					game.handler_key(e.key.code);
					break;
				default:
					break;
			}
		}
			game.game_actions();
	}
	return 0;
}


int main() {
	srand(time(nullptr));
	game_cycle();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}