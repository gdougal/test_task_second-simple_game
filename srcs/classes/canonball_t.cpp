//
// Created by Gilberto Dougal on 4/22/21.
//

#include "canonball_t.hpp"

cannonball_t::cannonball_t() {
	interactable_ = true;
	radius_ = g_resourses.cannonball.radius;
	setTexture(g_resourses.cannonball.texture);
	setScale(vector2f (g_resourses.cannonball.texture_scale, g_resourses.cannonball.texture_scale));
	setOrigin(g_resourses.cannonball.origin);
	hp_ = 0;
	speed_ = g_resourses.cannonball.speed;
}

void cannonball_t::move() {
	vector2f a(speed_*getDirections().x, speed_*getDirections().y);
	setPosition(getPosition() - a);
}

cannonball_t *cannonball_t::clone(const direction &pos_and_dir) const {
	auto cannonball = new cannonball_t();
	cannonball->set_start(pos_and_dir);
	return cannonball;
}

void cannonball_t::set_start(const direction &startMv) {
	setPosition(startMv.first);
	directions_ = startMv.second;
}

