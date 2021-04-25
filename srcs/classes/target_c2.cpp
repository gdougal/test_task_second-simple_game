//
// Created by Gilberto Dougal on 4/24/21.
//

#include "target_c2.hpp"

target_c2::target_c2() {
	interactable_ = true;
	setTexture(g_resourses.target2.texture);
	setScale(g_resourses.target2.texture_scale, g_resourses.target2.texture_scale);
	setOrigin(g_resourses.target2.origin);
	radius_ = g_resourses.target2.radius;
	hp_ = g_resourses.target2.hp;
	speed_ = g_resourses.target2.speed;
}

void target_c2::move() {
	if (getPosition().x <= g_resourses.target1.left_border || getPosition().x >= g_resourses.target1.right_border) {
		directions_.x *= -1;
	}
	if (getPosition().y <= g_resourses.target1.top_border || getPosition().y >= g_resourses.target1.bot_border) {
		directions_.y *= -1;
	}
	vector2f step(speed_*directions_.x, speed_*directions_.y);
	setPosition(getPosition() + step);
}

target_c2 *target_c2::clone(const direction &pos_and_dir) const {
	auto	target2 = new target_c2();
	target2->set_start(random_pos_dir_generator());
	return target2;
}

void target_c2::set_start(const direction &startMv) {
	setPosition(startMv.first);
	directions_ = startMv.second;
}
