#include <iostream>
#include "classes/canonball_t.hpp"
#include "classes/cannon_t.hpp"
#include "classes/wrap_window.hpp"
#include "classes/target_c1.hpp"
#include "classes/target_c2.hpp"
#include <array>
#include <list>


float random_float(float min, float max) {
	return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}

class	logic {
private:
	typedef	std::list<cannonball_t>										t_balls_lst;
	typedef	std::list<I_target*>												t_target_lst;
	sf::RenderWindow																	*session_window;
	game_mangment																			manager_;
	cannon_t																					cannon_;
	t_balls_lst																				balls_;
	t_target_lst																			targets_;

public:

	void	generate_targets() {
		for (int i = 0; i < 6; ++i) {
			targets_.push_back(target_c1().clone());
		}
		for (int i = 0; i < 4; ++i) {
			targets_.push_back(target_c2().clone());
		}
	}

	logic() {
		manager_.set_false_press();
		generate_targets();
	}
	virtual ~logic() {}

	void		update_game_logic() {
		cannon_.rotate_canon(*session_window);
		manager_.saw_at_clock();
		shooting();
		moving_cannonballs();
		collapse_targets();
		moving_targets();
	}

	void		draw_game_objects() {
		session_window->draw(cannon_.getScope());
		session_window->draw(cannon_);
		draw_targets();
		draw_cannonballs();
	}

	void	shooting() {
		if (!LEFT_MOUSE) {
			manager_.set_false_press();
		}
		else if (LEFT_MOUSE && !manager_.is_pressed()) {
			manager_.set_true_press();
			balls_.emplace_back(cannon_.top_dot());
		}
	}


	void collapse_targets() {
		for (auto& i: targets_) {
			for (auto& j: targets_) {
					j->collapse(i, j);
			}
		}
	}

	void	moving_targets() {
		for (auto it = targets_.begin(); it != targets_.end(); ++it) {
			(*it)->target_move();
		}
	}

	void	draw_targets() {
		for (auto& i: targets_) {
			session_window->draw(*i);
		}
	}

	void	moving_cannonballs() {
		for (auto it = balls_.begin(); it != balls_.end(); ) {
			it->cannonbal_move();
			if (it->getPosition().x < 0 || it->getPosition().y < 0)
				balls_.erase(it++);
			else
				++it;
		}
	}
	void	draw_cannonballs() {
		for (auto& i: balls_) {
			session_window->draw(i);
		}
	}
	void	setPubWindow(sf::RenderWindow *pubWindow) {session_window = pubWindow;}
};

int	drwning() {
	wrap_window window;
	logic game;
	game.setPubWindow(window.getPubWindow().get());

	while (window.getPubWindow()->isOpen()) {
		sf::Event e;
		while (window.getPubWindow()->pollEvent(e)) {

			switch (e.type) {
				case sf::Event::EventType::Closed:
					window.getPubWindow()->close();
					break;
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
	drwning();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}


//game current_session;
//current_session.cannon->balls
//
//update_logic(game )
//{
//	foreach(cannonball in current_session->cannon->balls)
//	{
//		cannonball->position += cannonball->sinus * CANNONBALL_SPEED;
//	}
//}
//
//draw(game)
//{
//	foreach(cannonball in current_session->cannon->balls)
//	{
//		sf::draw(cannonball->sprite, cannonball->position);
//	}
//}
//
//while (1)
//{
//
//	update_logic()
//	{
//
//	}
//
//	draw();
//}

//int main()
//{
//	// Create the main window
//	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
//	// Load a sprite to display
//	sf::Texture texture;
//	if (!texture.loadFromFile("cute_image.jpg"))
//		return EXIT_FAILURE;
//	sf::Sprite sprite(texture);
//	// Create a graphical text to display
//	sf::Font font;
//	if (!font.loadFromFile("arial.ttf"))
//		return EXIT_FAILURE;
//	sf::Text text("Hello SFML", font, 50);
//	// Load a music to play
//	sf::Music music;
//	if (!music.openFromFile("nice_music.ogg"))
//		return EXIT_FAILURE;
//	// Play the music
//	music.play();
//	// Start the game loop
//	while (window.isOpen())
//	{
//		// Process events
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			// Close window: exit
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		// Clear screen
//		window.clear();
//		// Draw the sprite
//		window.draw(sprite);
//		// Draw the string
//		window.draw(text);
//		// Update the window
//		window.display();
//	}
//	return EXIT_SUCCESS;
//}