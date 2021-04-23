//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_SHOOTING_RANGE_HPP
#define HELLO_SFML_SHOOTING_RANGE_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

static const uint						g_win_width = 1440;
static const uint						g_win_height = 2560;
static const uint						g_framerate = 200.f;

typedef	sf::RenderWindow				win_t;
typedef	sf::Vector2<float>			vector2f;
typedef	sf::Vector2<int>				vector2i;
typedef	std::pair<vector2f, 		vector2f>	direction;
#define	RAD_TO_DEGREE						M_PI/180.f
#define	DEGREE_TO_RAD						180.f/M_PI
#define	BALL_SPEED							(g_framerate/4.f)
#define	TARGET_SPEED(multiply)	(g_framerate/multiply)
#define	TEXTURE_SCOPE						"Tir_objects_png/Aim.png"
#define	TEXTURE_CANNON					"Tir_objects_png/Cut_cannon.png"
#define	TEXTURE_CANNONBALL			"Tir_objects_png/cut_cannonball.png"
#define	TEXTURE_TARGET1					"Tir_objects_png/cut_target1.png"
#define	TEXTURE_TARGET2					"Tir_objects_png/cut_target2.png"
#define	TEXTURE_STAND						"Tir_objects_png/Stand.png"
#define	HP_TARGET1							2

#define LEFT_MOUSE					sf::Mouse::isButtonPressed(sf::Mouse::Left)

float			angele(vector2f v0, vector2f v1);
float			random_float(float min, float max);
vector2f	normalize(vector2f v, vector2f v1);
float			lenght(vector2f v0, vector2f v1);

typedef struct				s_Time_mangment {
	sf::Clock						clock_;
	sf::Time						cur_time_;
	bool								pressed_;

	void								saw_at_clock()			{cur_time_ = clock_.getElapsedTime();}
	void								set_true_press()		{pressed_ = true;}
	void								set_false_press()		{pressed_ = false;}
	bool								is_pressed() const	{return pressed_;}
}											game_mangment;



#endif //HELLO_SFML_SHOOTING_RANGE_HPP
