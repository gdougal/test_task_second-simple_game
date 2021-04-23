//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_CANONBALL_T_HPP
#define HELLO_SFML_CANONBALL_T_HPP
#include "../shooting_range.hpp"

class	cannonball_t: public sf::Sprite {
private:
//	sf::Time						curent_time;
	sf::Texture					canonball_texture_;
	sf::Vector2<float>	start_mv_;
	sf::Vector2<float>	r_cos_sin_;
public:
	cannonball_t():
	start_mv_(0, 0),
	r_cos_sin_(0, 0)
	{
		if (!canonball_texture_.loadFromFile(TEXTURE_CANNONBALL))
			throw(std::exception()); /// Is this right?
		setTexture(canonball_texture_);
		setScale(sf::Vector2<float>(0.5f,0.5f));
		setOrigin(static_cast<float>(getTexture()->getSize().x)/2, static_cast<float>(getTexture()->getSize().y)/2);
	}

	void setStartMv(const direction &startMv) {
		start_mv_ = startMv.first;
		r_cos_sin_ = startMv.second;
		setPosition(start_mv_);
	}

	void Move() {
		sf::Vector2<float> a(BALL_SPEED*r_cos_sin_.x, BALL_SPEED*r_cos_sin_.y);
		start_mv_ = start_mv_ - a;
		setPosition(start_mv_);
	}

	const sf::Vector2<float> &getStartMv() const {return start_mv_;}
	const sf::Vector2<float> &getRCosSin() const {return r_cos_sin_;}

//	cannonball_t(const cannonball_t& ref): cannonball_t() {
//		if (this != &ref) {
//			*this = ref;
//		}
//	}

//	cannonball_t&		operator=(const cannonball_t& ref) {
//		if (this != &ref) {
//		}
//		return *this;
//	}

//	bool isHidden() const {return hidden_;}
//	void setHidden(bool hidden = true) {cannonball_t::hidden_ = hidden;}

	virtual ~cannonball_t() {}
};

#endif //HELLO_SFML_CANONBALL_T_HPP
