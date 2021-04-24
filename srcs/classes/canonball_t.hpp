//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_CANONBALL_T_HPP
#define HELLO_SFML_CANONBALL_T_HPP
#include "A_projectile.hpp"
#include <iostream>

class	cannonball_t: public sf::Sprite {
private:
	vector2f								directions_;
	const float							radius_ = g_resourses.cannonball.radius;
public:
	cannonball_t() = delete;
	explicit	cannonball_t(const direction &startMv):
	directions_(startMv.second)
	{
		setTexture(g_resourses.cannonball.texture);
		setScale(vector2f (g_resourses.cannonball.texture_scale, g_resourses.cannonball.texture_scale));
		setOrigin(g_resourses.cannonball.origin);
		setPosition(startMv.first);
	}

	void	move() {
		vector2f a(g_resourses.cannonball.speed*directions_.x, g_resourses.cannonball.speed*directions_.y);
		setPosition(getPosition() - a);
	}

	float						getRadius()				const	{ return radius_; }
	const vector2f	&getDirections()	const	{ return directions_; }

	virtual ~cannonball_t() {}
};

#endif //HELLO_SFML_CANONBALL_T_HPP
