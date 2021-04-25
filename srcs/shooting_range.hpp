//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_SHOOTING_RANGE_HPP
#define HELLO_SFML_SHOOTING_RANGE_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <exception>

static const float						g_win_height = 2560;
static const float						g_win_width = g_win_height/16*9;
static const float						g_framerate = 60.f;

static const int							g_targets_small_num = 300;
static const int							g_targets_big_num = 10;

typedef	sf::RenderWindow							win_t;
typedef	sf::Vector2<float>						vector2f;
typedef	std::pair<vector2f, vector2f>	direction;
#define	RAD_TO_DEGREE									M_PI/180.f
#define	DEGREE_TO_RAD									180.f/M_PI
#define	HALF													0.5f
#define	SQREEN_GAME_ZONE							0.7f
#define	MULTIPLU_BOMB_RADIUS					4.f
#define	MOVE_SPEED(multiply)					(g_framerate/(g_win_height/multiply))
#define	SCALE(multiply)								(multiply * g_win_height) / static_cast<float>(texture.getSize().y)
#define	TEXTURE_SCOPE									"Tir_objects_png/Aim.png"
#define	TEXTURE_CANNON								"Tir_objects_png/Cut_cannon.png"
#define	TEXTURE_CANNONBALL						"Tir_objects_png/cut_cannonball.png"
#define TEXTURE_BOMB									"Tir_objects_png/cutBomb.png"
#define	TEXTURE_TARGET1								"Tir_objects_png/cut_target1.png"
#define	TEXTURE_TARGET2								"Tir_objects_png/cut_target2.png"
#define LEFT_MOUSE										sf::Keyboard::isKeyPressed(sf::Keyboard::Space)

float			angele(vector2f v0, vector2f v1);
float			random_float(float min, float max);
vector2f	normalize(vector2f v, vector2f v1);
float			lenght_(vector2f v0, vector2f v1);
direction	random_pos_dir_generator();

template <class T, class T1>
bool is_object(T* ref) {
	if (dynamic_cast<T1*>(ref))
		return true;
	else
		return false;
}

typedef	struct	s_resource {
	sf::Texture						texture;
	float									multiply_scale;
	float									texture_scale;
	float									radius;
	vector2f							origin;
	float									speed;
	int										hp;

	float									top_border;
	float									bot_border;
	float									left_border;
	float									right_border;

	s_resource(const float multiplyScale, const char* texture_path, const float multiplySpeed, const int8_t HP) {
		multiply_scale = multiplyScale;
		texture.loadFromFile(texture_path);
		speed = MOVE_SPEED(multiplySpeed);
		texture_scale = SCALE(multiply_scale);
		origin = vector2f(static_cast<float>(texture.getSize().x) * HALF, static_cast<float>(texture.getSize().y) * HALF);
		radius = static_cast<float>(texture.getSize().x) * texture_scale * 0.5f;
		left_border = top_border = radius;
		bot_border = g_win_height * SQREEN_GAME_ZONE;
		right_border = g_win_width - radius;
		hp = HP;
	};
}								sprite_balls;

typedef	struct	s_resource_general {
	sf::Texture						texture;
	float									multiply_scale;
	float									texture_scale;
	vector2f							origin;
	s_resource_general(const float multiplyScale, const char* texture_path, float origin_delim) {
		multiply_scale = multiplyScale;
		texture.loadFromFile(texture_path);
		texture_scale = SCALE(multiply_scale);
		origin = vector2f (static_cast<float>(texture.getSize().x)*HALF, static_cast<float>(texture.getSize().y)*origin_delim);
	};
}								sprite_general;

typedef struct	s_resourses {
private:
	static constexpr float	cannon_texture_scale = 0.15f;
	static constexpr float	scope_texture_scale = 0.05f;
	static constexpr float	cannonball_texture_scale = 0.04f;
	static constexpr float	bomb_texture_scale = 0.08f;
	static constexpr float	target1_texture_scale = 0.03f;
	static constexpr float	target2_texture_scale = 0.05f;

	static constexpr float	cannonball_multiply_speed = 1200.f;
	static constexpr float	target1_multiply_speed = 700.f;
	static constexpr float	target2_multiply_speed = 550.f;

	static constexpr float	canon_denominator_origin_y = 1.f;
	static constexpr float	scope_denominator_origin_y = 0.5;
	static constexpr int8_t	hp_cannonball = 0;
	static constexpr int8_t hp_target1		= 3;
	static constexpr int8_t hp_target2		= 2*hp_target1;
public:
	sprite_general	cannon{cannon_texture_scale, TEXTURE_CANNON, canon_denominator_origin_y};
	sprite_general	scope{scope_texture_scale, TEXTURE_SCOPE, scope_denominator_origin_y};
	sprite_balls		cannonball{cannonball_texture_scale, TEXTURE_CANNONBALL ,cannonball_multiply_speed, hp_cannonball};
	sprite_balls		bomb{bomb_texture_scale, TEXTURE_BOMB, cannonball_multiply_speed, hp_cannonball};
	sprite_balls		target1{target1_texture_scale, TEXTURE_TARGET1, target1_multiply_speed, hp_target1};
	sprite_balls		target2{target2_texture_scale, TEXTURE_TARGET2, target2_multiply_speed, hp_target2};
}								t_resourses;

static t_resourses			g_resourses;

#endif //HELLO_SFML_SHOOTING_RANGE_HPP
