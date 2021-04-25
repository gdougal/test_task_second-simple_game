//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_TARGET_C1_HPP
#define HELLO_SFML_TARGET_C1_HPP
#include "interaction_objects.hpp"


class target_c1: public interacion_obj {
public:
	explicit	target_c1() {
		interactable_ = true;
		setTexture(g_resourses.target1.texture);
		setScale(g_resourses.target1.texture_scale, g_resourses.target1.texture_scale);
		setOrigin(g_resourses.target1.origin);
		radius_ = g_resourses.target1.radius;
		hp_ = g_resourses.target1.hp;
		speed_ = g_resourses.target1.speed;
	}

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

	target_c1* clone(const direction& pos_and_dir) const override {
		auto	target1 = new target_c1();
		target1->set_start(pos_and_dir);
		return target1;
	}

	void					set_start(const direction &startMv) override {
		setPosition(startMv.first);
		directions_ = startMv.second;
	}
	virtual ~target_c1() override {};
};


#endif //HELLO_SFML_TARGET_C1_HPP
