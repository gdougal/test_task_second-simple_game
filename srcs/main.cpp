#include <iostream>
#include "classes/logic.hpp"




int	game_cycle(const std::string	conf_dir = std::string("./config.txt")) {
	try {
		logic game(conf_dir);
		wrap_window window(game.getResourses().getWinResourse());
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
	catch (...) {
		return 1;
	}
}


int main(int argc, char** argv) {
	srand(time(nullptr));
	int ret = 0;
	if (argc == 1)
		ret = game_cycle();
	else if (argc > 1)
		ret = game_cycle(argv[1]);
	if (ret) {
		std::cout << "oups, some trouble... maybe config path?" << std::endl;
	}
	return 0;
}