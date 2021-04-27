//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_SHOOTING_RANGE_HPP
#define HELLO_SFML_SHOOTING_RANGE_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <exception>
#include "classes/config/Config.hpp"


typedef	sf::RenderWindow							win_t;
typedef	sf::Vector2<float>						vector2f;
typedef	std::pair<vector2f, vector2f>	direction;
#define	RAD_TO_DEGREE									M_PI/180.f
#define	DEGREE_TO_RAD									180.f/M_PI
#define	HALF													0.5f

class		win_resource {
	float	multiply_game_sqreen;
	float	multiply_boom_radius;
	float	win_height;
	float	win_width;
	float	framerate;
	int		small_yellow_num;
	int		big_green_num;
	bool	mouse_cursor_grabbed;
	bool	key_repeat_enabled;
	bool	mouse_cursor_visible;
public:
	win_resource(const Config::Section& configure) {
		multiply_game_sqreen = configure.getFloatVal("multiply_game_sqreen");
		multiply_boom_radius = configure.getFloatVal("multiply_boom_radius");
		win_height = configure.getFloatVal("win_height");
		win_width = configure.getFloatVal("win_width");
		framerate = configure.getFloatVal("framerate");
		small_yellow_num = configure.getIntVal("small_yellow_num");
		big_green_num = configure.getIntVal("big_green_num");
		mouse_cursor_grabbed = configure.getBoolVal("mouse_cursor_grabbed");
		key_repeat_enabled = configure.getBoolVal("key_repeat_enabled");
		mouse_cursor_visible = configure.getBoolVal("mouse_cursor_visible");
	}
	float	getMultiplyGameSqreen()	const { return multiply_game_sqreen; }
	float	getMultiplyBoomRadius()	const { return multiply_boom_radius; }
	float	getWinHeight()					const { return win_height; }
	float	getWinWidth()						const { return win_width; }
	float	getFramerate()					const { return framerate; }
	int		getSmallYellowNum()			const { return small_yellow_num; }
	int		getBigGreenNum()				const { return big_green_num; }
	bool	isMouseCursorGrabbed()	const { return mouse_cursor_grabbed; }
	bool	isKeyRepeatEnabled()		const { return key_repeat_enabled; }
	bool	isMouseCursorVisible()	const { return mouse_cursor_visible; }

	uint	getFramerateUint()			const { return static_cast<uint>(framerate); }
	uint	getWinHeightUint()			const { return static_cast<uint>(win_height); }
	uint	getWinWidthUint()				const { return static_cast<uint>(win_width); }
};

class	sprite_balls {
	std::shared_ptr<sf::Texture>	texture;
	float													texture_scale;
	float													radius;
	vector2f											origin;
	float													speed;
	int														hp;

	float													top_border;
	float													bot_border;
	float													left_border;
	float													right_border;
	std::shared_ptr<sf::Texture>	explose_text;
public:
	sprite_balls(const Config::Section& configure, const Config::Section& win_configure)
		: texture(new sf::Texture()),
			explose_text(new sf::Texture())
	{
		float prefer_resolution = std::max(win_configure.getFloatVal("win_height"), win_configure.getFloatVal("win_width"));

		float multiply_scale = configure.getFloatVal("multiply_scale_texture");
		if (!texture->loadFromFile(configure.getStringVal("path")))
			throw std::invalid_argument("Wrong configure file (maybe)");
		if (!explose_text->loadFromFile(configure.getStringVal("path_explose")))
			throw std::invalid_argument("Wrong configure file (maybe)");
		texture_scale = (multiply_scale * prefer_resolution) / static_cast<float>(texture->getSize().y);
		origin = vector2f(static_cast<float>(texture->getSize().x) * HALF, static_cast<float>(texture->getSize().y) * HALF);
		radius = static_cast<float>(texture->getSize().x) * texture_scale * 0.5f;
		speed = (win_configure.getFloatVal("framerate") * texture_scale * configure.getFloatVal("multiply_scale_speed"));
		left_border = top_border = radius;
		hp = configure.getIntVal("hp");
		bot_border = win_configure.getFloatVal("win_height") * win_configure.getFloatVal("multiply_game_sqreen");
		right_border = win_configure.getFloatVal("win_width") - left_border;
	};


	const sf::Texture	&getTexture()			const { return *texture; }
	float							getTextureScale()	const { return texture_scale; }
	float							getRadius()				const { return radius; }
	const vector2f		&getOrigin()			const { return origin; }
	float							getSpeed()				const { return speed; }
	int								getHp()						const { return hp; }
	float							getTopBorder()		const	{ return top_border; }
	float							getBotBorder()		const	{ return bot_border; }
	float							getLeftBorder()		const	{ return left_border; }
	float							getRightBorder()	const	{ return right_border; }
	const sf::Texture &getExploseText() const { return *explose_text; }
};

typedef	class	s_resource_general {
	std::shared_ptr<sf::Texture>	texture;
	float													texture_scale;
	vector2f											origin;
public:
	s_resource_general(const Config::Section& configure, const Config::Section& win_configure)
		: texture(new sf::Texture())
	{
		float prefer_resolution = std::max(win_configure.getFloatVal("win_height"), win_configure.getFloatVal("win_width"));

		float multiply_scale = configure.getFloatVal("multiply_scale_texture");
		if (!texture->loadFromFile(configure.getStringVal("path")))
			throw std::invalid_argument("Wrong configure file (maybe)");
		texture_scale = (multiply_scale * prefer_resolution) / static_cast<float>(texture->getSize().y);
		origin = vector2f (static_cast<float>(texture->getSize().x)*HALF, static_cast<float>(texture->getSize().y)*configure.getFloatVal("denominator_origin_y"));
	};

	const	sf::Texture	&getTexture()			const { return *texture; }
	const float				getTextureScale()	const { return texture_scale; }
	const	vector2f		&getOrigin()			const { return origin; }
}								sprite_general;


class t_managment {
	sf::Clock										swatch_;
	std::shared_ptr<sf::Font>		font_;
	std::shared_ptr<sf::Text>		score_text_;
	std::shared_ptr<sf::Text>		time_;
	std::shared_ptr<sf::Sprite>	background_;
	uint												score_;
	bool												bomb_inplace_;
	bool												pause_;
public:
	t_managment(const Config::Section& win_configure):
		font_(new sf::Font()),
		score_text_(new sf::Text),
		time_(new sf::Text),
		background_(new sf::Sprite()),
		score_(0),
		bomb_inplace_(false)
	{
		if (!font_->loadFromFile(win_configure.getStringVal("font")))
			throw std::invalid_argument("Wrong configure file (maybe)");
		time_->setFont(*font_);
		score_text_->setFont(*font_);
		time_->setCharacterSize(win_configure.getIntVal("win_height") / 50);
		score_text_->setCharacterSize(win_configure.getIntVal("win_height") / 50);
		time_->setFillColor(sf::Color(255,255,255));
		score_text_->setFillColor(sf::Color(255,255,255));
	};
};

class	t_resourses {
private:
	typedef std::shared_ptr<win_resource> win_resource_ptr;
	typedef std::shared_ptr<sprite_general> sprite_general_ptr;
	typedef std::shared_ptr<sprite_balls> sprite_balls_ptr;
	win_resource_ptr			win_resourse;
	sprite_general_ptr		cannon;
	sprite_general_ptr		scope;
	sprite_balls_ptr			cannonball;
	sprite_balls_ptr			bomb;
	sprite_balls_ptr			target_small_yellow;
	sprite_balls_ptr			target_big_green;

public:
	t_resourses(const Config& configs):
		win_resourse(new win_resource(configs.getSection("GAME_WINDOW"))),
		cannon(new sprite_general(configs.getSection("CANNON"), configs.getSection("GAME_WINDOW"))),
		scope(new sprite_general(configs.getSection("SCOPE"), configs.getSection("GAME_WINDOW"))),
		cannonball(new sprite_balls(configs.getSection("CANNONBALL"), configs.getSection("GAME_WINDOW"))),
		bomb(new sprite_balls(configs.getSection("BOMB"), configs.getSection("GAME_WINDOW"))),
		target_small_yellow(new sprite_balls(configs.getSection("TARGET:SMALL_YELLOW"), configs.getSection("GAME_WINDOW"))),
		target_big_green(new sprite_balls(configs.getSection("TARGET:BIG_GREEN"), configs.getSection("GAME_WINDOW")))
	{}

	const sprite_general	&getCannon()						const { return *cannon; }
	const sprite_general	&getScope()							const { return *scope; }
	const sprite_balls		&getCannonball()				const { return *cannonball; }
	const sprite_balls		&getBomb()							const { return *bomb; }
	const sprite_balls		&getTargetSmallYellow()	const { return *target_small_yellow; }
	const sprite_balls		&getTargetBigGreen()		const { return *target_big_green; }
	const win_resource		&getWinResourse()				const { return *win_resourse; }
};


template <class T, class T1>
bool is_object(T* ref) {
	if (dynamic_cast<T1*>(ref))
		return true;
	else
		return false;
}

float			angele(vector2f v0, vector2f v1);
float			random_float(float min, float max);
vector2f	normalize(vector2f v, vector2f v1);
float			lenght_(vector2f v0, vector2f v1);
direction	random_pos_dir_generator(const t_resourses& res);


#endif //HELLO_SFML_SHOOTING_RANGE_HPP
