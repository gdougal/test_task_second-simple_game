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


enum {
	GAME = true,
	PAUSE = false,
};


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
	sf::Clock											swatch_;
	std::shared_ptr<sf::Font>			font_;
	std::shared_ptr<sf::Text>			score_text_;
	std::shared_ptr<sf::Text>			time_text_;
	std::shared_ptr<sf::Sprite>		background_;
	int														score_;

	bool													bomb_inplace_;
	bool													game_mode_;
	int														bomb_damage_;
	int														standard_damage_;
	std::pair<sf::Time, sf::Time>	pause_time_;
	float													all_correction_time_;

	int														round_time_;
public:
	t_managment(const Config::Section& win_configure):
					font_(new sf::Font()),
					score_text_(new sf::Text),
					time_text_(new sf::Text),
					background_(new sf::Sprite()),
					score_(0),
					bomb_inplace_(false),
					game_mode_(true),
					all_correction_time_(0),
					pause_time_(sf::Time::Zero,sf::Time::Zero)
	{
		int resolution_x = win_configure.getIntVal("win_width");
		int resolution_y = win_configure.getIntVal("win_height");
		round_time_ = win_configure.getIntVal("round_time_sec");
		bomb_damage_ = win_configure.getIntVal("bomb_damage");
		standard_damage_ = win_configure.getIntVal("standard_damage");
		if (!font_->loadFromFile(win_configure.getStringVal("font")))
			throw std::invalid_argument("Wrong configure file (maybe)");

		score_text_->setFont(*font_);
		score_text_->setCharacterSize(resolution_y / 50.f);
		score_text_->setFillColor(sf::Color(255,255,255));
		score_text_->setOrigin(0, score_text_->getCharacterSize());
		score_text_->setPosition(0 + score_text_->getCharacterSize(), resolution_y - score_text_->getCharacterSize()*2);
		time_text_->setFont(*font_);
		time_text_->setCharacterSize(win_configure.getIntVal("win_height") / 50.f);
		time_text_->setFillColor(sf::Color(255,255,255));
		time_text_->setOrigin(0, time_text_->getCharacterSize());
		time_text_->setPosition((resolution_x/4.f)*3.f, resolution_y - time_text_->getCharacterSize()*2);
	};

	const std::shared_ptr<sf::Text>		&getScoreText()			const {
		score_text_->setString("Score: "+ std::to_string(score_));
		return score_text_;
	}

	const std::shared_ptr<sf::Text>		&getTimeText()					const {
		if (game_mode_ == GAME) {
				time_text_->setString("Time: " + std::to_string(round_time_ - curent_time()));
		}
		return time_text_;
	}



	const sf::Clock										&getSwatch()									const { return swatch_; }
	const std::shared_ptr<sf::Sprite>	&getBackground()							const {
		background_->setColor(sf::Color(swatch_.getElapsedTime().asSeconds() - all_correction_time_));
		return background_;
	}

	int																getBombDamage()								const { return bomb_damage_; }
	int																getStandardDamage()						const { return standard_damage_; }
	bool															isBombInplace()								const { return bomb_inplace_; }
	int																isGameMode()									const { return game_mode_; }
	int																isRoundEnd()									const { return round_time_ - curent_time() < 0; }
	void															ChangeBombInplace()									{ bomb_inplace_ = !bomb_inplace_; }
	void															ChangeGameMode()										{ game_mode_ = !game_mode_; }
	void															addScoreBomb()											{ score_ += bomb_damage_; }
	void															addScoreStandard()									{ score_ += standard_damage_; }
	void															relosdScore()												{ score_ = 0; }
	int																curent_time()									const	{ return static_cast<int>(swatch_.getElapsedTime().asSeconds() - all_correction_time_); }
	float															deltaPause()									const	{ return pause_time_.second.asSeconds() - pause_time_.first.asSeconds(); }

	void															fillPauseStart()	{
		pause_time_.first = swatch_.getElapsedTime();
	}
	void															fillPauseEnd()		{
		pause_time_.second = swatch_.getElapsedTime();
		all_correction_time_ +=deltaPause();
	}

	void															AddAllCorrectionTime()								{ all_correction_time_ += curent_time(); }
private:
};


class	t_resourses {
	typedef std::shared_ptr<win_resource> win_resource_ptr;
	typedef std::shared_ptr<sprite_general> sprite_general_ptr;
	typedef std::shared_ptr<sprite_balls> sprite_balls_ptr;
	typedef std::shared_ptr<t_managment> managment_ptr;
	win_resource_ptr			win_resourse;
	sprite_general_ptr		cannon;
	sprite_general_ptr		scope;
	sprite_balls_ptr			cannonball;
	sprite_balls_ptr			bomb;
	sprite_balls_ptr			target_small_yellow;
	sprite_balls_ptr			target_big_green;
	managment_ptr					managment;

public:
	t_resourses(const Config& configs):
		win_resourse(new win_resource(configs.getSection("GAME_WINDOW"))),
		cannon(new sprite_general(configs.getSection("CANNON"), configs.getSection("GAME_WINDOW"))),
		scope(new sprite_general(configs.getSection("SCOPE"), configs.getSection("GAME_WINDOW"))),
		cannonball(new sprite_balls(configs.getSection("CANNONBALL"), configs.getSection("GAME_WINDOW"))),
		bomb(new sprite_balls(configs.getSection("BOMB"), configs.getSection("GAME_WINDOW"))),
		target_small_yellow(new sprite_balls(configs.getSection("TARGET:SMALL_YELLOW"), configs.getSection("GAME_WINDOW"))),
		target_big_green(new sprite_balls(configs.getSection("TARGET:BIG_GREEN"), configs.getSection("GAME_WINDOW"))),
		managment(new t_managment(configs.getSection("GAME_WINDOW")))
	{}

	const sprite_general	&getCannon()						const { return *cannon; }
	const sprite_general	&getScope()							const { return *scope; }
	const sprite_balls		&getCannonball()				const { return *cannonball; }
	const sprite_balls		&getBomb()							const { return *bomb; }
	const sprite_balls		&getTargetSmallYellow()	const { return *target_small_yellow; }
	const sprite_balls		&getTargetBigGreen()		const { return *target_big_green; }
	const win_resource		&getWinResourse()				const { return *win_resourse; }
	const managment_ptr		&getManagment()					const { return managment; }
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
