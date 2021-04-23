//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_SHOOTING_RANGE_HPP
#define HELLO_SFML_SHOOTING_RANGE_HPP
#include <SFML/Graphics.hpp>
#include <cmath>

static const uint						g_win_width = 1080;
static const uint						g_win_height = 1920;
static const uint						g_framerate = 200.f;

typedef	sf::RenderWindow		win_t;
typedef sf::Vector2<float>	vector2f;
typedef sf::Vector2<int>		vector2i;
typedef	std::pair<vector2f, vector2f>	direction;
#define	RAD_TO_DEGREE				M_PI/180.f
#define	DEGREE_TO_RAD				180.f/M_PI
#define	BALL_SPEED					(g_framerate/10.f)
#define	TEXTURE_SCOPE				"Tir_objects_png/Aim.png"
#define	TEXTURE_CANNON			"Tir_objects_png/Cut_cannon.png"
#define	TEXTURE_CANNONBALL	"Tir_objects_png/Cannonball.png"
#define	TEXTURE_TARGET1			"Tir_objects_png/Target.png"
#define	TEXTURE_STAND				"Tir_objects_png/Stand.png"

#define NUMBER_BALLS				30
#define LEFT_MOUSE					sf::Mouse::isButtonPressed(sf::Mouse::Left)

#endif //HELLO_SFML_SHOOTING_RANGE_HPP
