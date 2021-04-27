//
// Created by Gilberto Dougal on 4/22/21.
//

#include "canonball_t.hpp"

cannonball_t::cannonball_t(const sprite_balls& config): interacion_obj(config) {
	interactable_ = true;
}

void cannonball_t::move() {
	vector2f a(speed_*getDirections().x, speed_*getDirections().y);
	setPosition(getPosition() - a);
}

cannonball_t *cannonball_t::clone(const direction &pos_and_dir, const sprite_balls& config) const {
	auto cannonball = new cannonball_t(config);
	cannonball->set_start(pos_and_dir);
	return cannonball;
}

void cannonball_t::set_start(const direction &startMv) {
	setPosition(startMv.first);
	directions_ = startMv.second;
}

