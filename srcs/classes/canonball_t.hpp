//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_CANONBALL_T_HPP
#define HELLO_SFML_CANONBALL_T_HPP
#include "../shooting_range.hpp"
#include <iostream>

class	cannonball_t: public sf::Sprite {
private:
	sf::Texture	canonball_texture_;
	vector2f		directions_;
	float				radius_;
public:
	cannonball_t() = default;
	explicit cannonball_t(const direction &startMv):
	directions_(startMv.second)
	{
		if (!canonball_texture_.loadFromFile(TEXTURE_CANNONBALL))
			throw(std::exception()); /// Is this right?
		setTexture(canonball_texture_);
		setScale(vector2f (0.5f,0.5f));
		setOrigin(static_cast<float>(getTexture()->getSize().x)/2, static_cast<float>(getTexture()->getSize().y)/2);
		setPosition(startMv.first);
		radius_ = static_cast<float >(getTexture()->getSize().x) * getScale().x;
	}


	void cannonbal_move() {
		vector2f a(BALL_SPEED*directions_.x, BALL_SPEED*directions_.y);
		setPosition(getPosition() - a);
	}

	virtual ~cannonball_t() {}
};

#endif //HELLO_SFML_CANONBALL_T_HPP
