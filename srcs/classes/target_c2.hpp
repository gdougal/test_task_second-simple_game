//
// Created by Gilberto Dougal on 4/24/21.
//

#ifndef HELLO_SFML_TARGET_C2_HPP
#define HELLO_SFML_TARGET_C2_HPP
#include "interaction_objects.hpp"

class target_c2: public interacion_obj {
public:

	target_c2() {
		interactable_ = true;
		setTexture(g_resourses.target2.texture);
		setScale(g_resourses.target2.texture_scale, g_resourses.target2.texture_scale);
		setOrigin(g_resourses.target2.origin);
		radius_ = g_resourses.target2.radius;
		hp_ = g_resourses.target2.hp;
		speed_ = g_resourses.target2.speed;
	}

	target_c2(const target_c2 &ref) = default;
	target_c2 &operator=(const target_c2 &ref) = default;

	void move() override {
		if (getPosition().x <= g_resourses.target1.left_border || getPosition().x >= g_resourses.target1.right_border) {
			directions_.x *= -1;
		}
		if (getPosition().y <= g_resourses.target1.top_border || getPosition().y >= g_resourses.target1.bot_border) {
			directions_.y *= -1;
		}
		vector2f step(speed_*directions_.x, speed_*directions_.y);
		setPosition(getPosition() + step);
	}

	target_c2* clone(const direction& pos_and_dir) const override {
		auto	target2 = new target_c2();
		target2->set_start(random_pos_dir_generator());
		return target2;
	}

	void					set_start(const direction &startMv) override {
		setPosition(startMv.first);
		directions_ = startMv.second;
	}
	virtual ~target_c2() override {};
};


#endif //HELLO_SFML_TARGET_C2_HPP
