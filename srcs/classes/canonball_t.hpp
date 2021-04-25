//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_CANONBALL_T_HPP
#define HELLO_SFML_CANONBALL_T_HPP
#include "interaction_objects.hpp"

class	cannonball_t: public interacion_obj {
public:
	cannonball_t() {
		interactable_ = true;
		radius_ = g_resourses.cannonball.radius;
		setTexture(g_resourses.cannonball.texture);
		setScale(vector2f (g_resourses.cannonball.texture_scale, g_resourses.cannonball.texture_scale));
		setOrigin(g_resourses.cannonball.origin);
		hp_ = 0;
		speed_ = g_resourses.cannonball.speed;
	}

	void	move() override {
		vector2f a(speed_*getDirections().x, speed_*getDirections().y);
		setPosition(getPosition() - a);
	}

	cannonball_t* clone(const direction &pos_and_dir) const override {
	auto cannonball = new cannonball_t();
	cannonball->set_start(pos_and_dir);
	return cannonball; }

	void					set_start(const direction &startMv) override {
		setPosition(startMv.first);
		directions_ = startMv.second;
	}

	virtual ~cannonball_t() {}
};

#endif //HELLO_SFML_CANONBALL_T_HPP
