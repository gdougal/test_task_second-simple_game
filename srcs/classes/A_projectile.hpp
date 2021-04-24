//
// Created by Gilberto Dougal on 4/24/21.
//

#ifndef HELLO_SFML_A_PROJECTILE_HPP
#define HELLO_SFML_A_PROJECTILE_HPP
#include "interaction_objects.hpp"

class A_projectile: public sf::Sprite {
private:
	vector2f					directions_;
	float							radius_;
public:
	A_projectile() {}
	A_projectile(const vector2f& directions, const float& radius) : directions_(
					directions), radius_(radius) {}
	virtual void						move() = 0;
	virtual float						getRadius()				const	{ return radius_; }
	virtual const vector2f	&getDirections()	const	{ return directions_; }

	virtual ~A_projectile() {};
};


#endif //HELLO_SFML_A_PROJECTILE_HPP
