#include <iostream>
#include "classes/logic.hpp"

int	drwning() {
	wrap_window	window;
	logic				game(window.getPubWindow().get());

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
						game.stop();
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