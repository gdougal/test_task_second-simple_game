//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_CANONBALL_T_HPP
#define HELLO_SFML_CANONBALL_T_HPP
#include "interaction_objects.hpp"

class	cannonball_t: public interacion_obj {
public:
	cannonball_t() = default;
	explicit	cannonball_t(const direction &startMv) {
		radius_ = g_resourses.cannonball.radius;
		setTexture(g_resourses.cannonball.texture);
		setScale(vector2f (g_resourses.cannonball.texture_scale, g_resourses.cannonball.texture_scale));
		setOrigin(g_resourses.cannonball.origin);
		setPosition(startMv.first);
		directions_ = startMv.second;
		hp_ = 0;
	}

	void	move() override {
		vector2f a(g_resourses.cannonball.speed*getDirections().x, g_resourses.cannonball.speed*getDirections().y);
		setPosition(getPosition() - a);
	}

	cannonball_t* clone(const direction &pos_and_dir) const override { return new cannonball_t(pos_and_dir); }

	virtual ~cannonball_t() {}
};

#endif //HELLO_SFML_CANONBALL_T_HPP
