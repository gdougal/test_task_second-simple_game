//
// Created by Gilberto Dougal on 4/23/21.
//

#include "target_c1.hpp"

target_c1::target_c1(const sprite_balls& config): interacion_obj(config) {
	interactable_ = true;
}

void target_c1::move() {
//	if (getPosition().x <= s_resource::getLeftBorder() || getPosition().x >= s_resource::getRightBorder()) {
//		directions_.x *= -1;
//	}
//	if (getPosition().y <= s_resource::getTopBorder() || getPosition().y >= s_resource::getBotBorder()) {
//		directions_.y *= -1;
//	}
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
