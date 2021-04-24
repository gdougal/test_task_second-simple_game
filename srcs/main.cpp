#include <iostream>
#include "classes/wrap_window.hpp"
#include "classes/cannon_t.hpp"
#include "classes/target_c2.hpp"
#include "classes/interaction.hpp"
#include "classes/target_c1.hpp"
#include "classes/canonball_t.hpp"
#include <list>

class	logic {
private:
	typedef	std::shared_ptr<interacion_obj>	ptr_;
	typedef	std::list<ptr_>							t_balls_lst;
	typedef	std::list<ptr_>					t_target_lst;
	sf::RenderWindow								*session_window;
	cannon_t												cannon_;
	t_balls_lst											balls_;
	t_target_lst										targets_;

public:

	void	generate_targets() {
		for (int i = 0; i < 50; ++i) {
			targets_.emplace_back(target_c1().clone(random_pos_dir_generator()));
		}
		for (int i = 0; i < 10; ++i) {
			targets_.emplace_back(target_c2().clone(random_pos_dir_generator()));
		}
	}

	logic() {
		generate_targets();
	}
	virtual ~logic() {}

	void		update_game_logic() {
		cannon_.rotate_canon(*session_window);
		collapse_targets();
		collapse_cannonbals();
		moving_cannonballs();
		moving_targets();
	}

	void		draw_game_objects() {
		draw_targets();
		session_window->draw(cannon_);
		draw_cannonballs();
		session_window->draw(cannon_.getScope());
	}

	void	shooting() {
		balls_.emplace_back(cannonball_t().clone(cannon_.top_dot()));
	}


	void collapse_targets() {
		for (auto it = targets_.begin(); it != targets_.end(); ++it) {
			for (auto it_i = it; it_i != targets_.end(); ++it_i) {
					interaction::collapse_targets(it->get(), it_i->get());
			}
		}
	}
	void collapse_cannonbals() {
		for (auto it = balls_.begin(); it != balls_.end(); ++it) {
			for (auto it_t = targets_.begin(); it_t != targets_.end(); ++it_t) {
				if (*it && *it_t && interaction::collapse_target_with_ball(it_t->get(), it->get())) {
					balls_.erase(it++);
					if (it == balls_.end())
						break;
					if ((*it_t)->getHp() == 0) {
						targets_.erase(it_t++);
					}
				}
			}
		}
	}

	void	moving_targets() {
		for (auto it = targets_.begin(); it != targets_.end(); ++it) {
			(*it)->move();
		}
	}


	void	moving_cannonballs() {
		for (auto it = balls_.begin(); it != balls_.end(); ) {
			(*it)->move();
			if ((*it)->getPosition().x < 0 || (*it)->getPosition().y < 0) {
				balls_.erase(it++);
			}
			else
				++it;
		}
	}

	void	draw_targets() {
		for (auto& i: targets_) {
			session_window->draw(*i);
		}
	}

	void	draw_cannonballs() {
		for (auto& i: balls_) {
			session_window->draw(*i);
		}
	}
	void	setPubWindow(sf::RenderWindow *pubWindow) {session_window = pubWindow;}
};

int	drwning() {
	wrap_window	window;
	logic				game;
	game.setPubWindow(window.getPubWindow().get());

	while (window.getPubWindow()->isOpen()) {
		sf::Event e;
		while (window.getPubWindow()->pollEvent(e)) {

			switch (e.type) {
				case sf::Event::EventType::Closed:
					window.getPubWindow()->close();
					break;
				case e.KeyPressed:
					game.shooting();
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