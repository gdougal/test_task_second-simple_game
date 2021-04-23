#include <iostream>
#include "classes/canonball_t.hpp"
#include "classes/scope_t.hpp"
#include <array>
#include <list>



typedef struct				s_Time_mangment {
	sf::Clock						clock_;
	sf::Time						cur_time_;
	sf::Time						prev_ball_;
	bool								pressed_;


	bool								next_ball() const		{return prev_ball_.asSeconds() + 0.5f < cur_time_.asSeconds();}
	void								set_start_mv_ball()	{prev_ball_ = cur_time_;}
	void								saw_at_clock()			{cur_time_ = clock_.getElapsedTime();}
	void								set_true_press()		{pressed_ = true;}
	void								set_false_press()		{pressed_ = false;}
	bool								is_pressed() const	{return pressed_;}
}											game_mangment;


float angele(vector2f v0, vector2f v1)
{
	return static_cast<float >(1.f - std::atan((v1.x - v0.x)/(v1.y - v0.y)) * DEGREE_TO_RAD);
}

class cannon_t: public sf::Sprite {
private:
	scope_t										scope_;
	sf::Texture								cannon_texture_;
public:
	cannon_t() {
		if (!cannon_texture_.loadFromFile(TEXTURE_CANNON))
			throw(std::exception()); /// Is this right?
		setTexture(cannon_texture_);
		setScale(vector2f(0.5f,0.5f));
		setOrigin(static_cast<float>(getTexture()->getSize().x)/2.f, static_cast<float>(getTexture()->getSize().y));
		setPosition(g_win_width/2.f, g_win_height);
	}

	void	rotate_canon(const win_t& window) {
		scope_.set_scope_pos(window);
		setRotation(angele(scope_.getPosition(), getPosition()));
	}

	direction	top_dot() {
		vector2f	curent;
		auto			tex_y = static_cast<float>(cannon_texture_.getSize().y)*getScale().y;
		auto			rotation = static_cast<float>((getRotation() + 90.f)*RAD_TO_DEGREE);
		vector2f	r_cos_sin(std::cosf(rotation), std::sinf(rotation));

		curent = getPosition() - vector2f(tex_y*r_cos_sin.x, tex_y*r_cos_sin.y);
		return (direction(curent, r_cos_sin));
	}

//	const cannonball_t&	getCannonball() const {return cannonball_;}
	const scope_t&			getScope() const {return scope_;}

	virtual ~cannon_t() {}
};



class	logic {
private:
//	bool																							pressed_;
	game_mangment																			manager_;
	cannon_t																					cannon_;
	std::array<cannonball_t, NUMBER_BALLS>						balls_;
	std::array<cannonball_t, NUMBER_BALLS>::iterator	cur_ball_;

public:
	sf::RenderWindow	pub_window;

	logic() : pub_window(sf::VideoMode(g_win_width, g_win_height), "Hello SFML (its me)") {
		pub_window.setFramerateLimit(g_framerate);
		pub_window.setMouseCursorVisible(false);
		pub_window.setMouseCursorGrabbed(true);
		pub_window.setKeyRepeatEnabled(false);
		cur_ball_ = balls_.begin();

		manager_.set_false_press();

//		pressed_ = false;
	}
	virtual ~logic() {}

	void		start_sqreen() {/*Display main menu*/
	};

//	sf::Mouse::isButtonPressed(sf::Mouse::Left)
//	pub_window.setMouseCursorGrabbed(true);
//		scope_.setScale((float )g_win_width/pub_window.getSize().x, (float)g_win_height/pub_window.getSize().y);
	void		draw() {
		manager_.saw_at_clock();
		cannon_.rotate_canon(pub_window);
		pub_window.draw(cannon_.getScope());
		pub_window.draw(cannon_);
		if (!LEFT_MOUSE) {
			manager_.set_false_press();
//			pressed_ = false;
		}
		if (LEFT_MOUSE && cur_ball_ != balls_.end() /*&& manager_.next_ball()*/ && !manager_.is_pressed()) {
			manager_.set_true_press();
//			pressed_ = true;
			cur_ball_->setStartMv(cannon_.top_dot());
			cur_ball_->Move();
			manager_.set_start_mv_ball();
			cur_ball_++;
		}
		for (auto& i: balls_) {
			if (i.getStartMv().x == 0)
				break ;
			i.Move();
			pub_window.draw(i);
		}
	}



};




int	drwning() {
	logic game;

	while (game.pub_window.isOpen()) {
		sf::Event e;
		while (game.pub_window.pollEvent(e)) {

			switch (e.type) {
				case sf::Event::EventType::Closed:
					game.pub_window.close();
					break;
			}
		}
		game.pub_window.clear();
		game.draw();
		game.pub_window.display();
	}
	return 0;
}


int main() {
	drwning();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}


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