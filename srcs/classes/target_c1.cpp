//
// Created by Gilberto Dougal on 4/23/21.
//

#include "target_c1.hpp"

target_c1::target_c1(const sprite_balls& config): interacion_obj(config) {
	interactable_ = true;
}

void target_c1::move() {
	if (getPosition().x <= g_resourses.target1.left_border || getPosition().x >= g_resourses.target1.right_border) {
		directions_.x *= -1;
	}
	if (getPosition().y <= g_resourses.target1.top_border || getPosition().y >= g_resourses.target1.bot_border) {
		directions_.y *= -1;
	}
	vector2f step(speed_*directions_.x, speed_*directions_.y);
	setPosition(getPosition() + step);
}

target_c1 *target_c1::clone(const direction &pos_and_dir, const sprite_balls& config) const {
	auto	target1 = new target_c1(config);
	target1->set_start(pos_and_dir);
	return target1;
}

void target_c1::set_start(const direction &startMv) {
	setPosition(startMv.first);
	directions_ = startMv.second;
}
