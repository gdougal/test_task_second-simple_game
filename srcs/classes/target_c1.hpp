//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_TARGET_C1_HPP
#define HELLO_SFML_TARGET_C1_HPP
#include "interaction_objects.hpp"


class target_c1: public interacion_obj {
public:
	target_c1() {
		float	x = random_float(g_resourses.target1.left_border, g_resourses.target1.right_border);
		float	y = random_float(g_resourses.target1.top_border, g_resourses.target1.bot_border);
		setTexture(g_resourses.target1.texture);
		setScale(g_resourses.target1.texture_scale, g_resourses.target1.texture_scale);
		setOrigin(g_resourses.target1.origin);
		radius_ = g_resourses.target1.radius;
		setPosition(x, y);
		directions_ = normalize(getPosition(), vector2f(random_float(0, g_win_width), random_float(0, g_win_width)));
		hp_ = g_resourses.target1.hp;
	};
	target_c1(const target_c1 &ref) = default;
	target_c1 &operator=(const target_c1 &ref) = default;

	void move() override {
		if (getPosition().x <= g_resourses.target1.left_border || getPosition().x >= g_resourses.target1.right_border) {
			directions_.x *= -1;
		}
		if (getPosition().y <= g_resourses.target1.top_border || getPosition().y >= g_resourses.target1.bot_border) {
			directions_.y *= -1;
		}
		vector2f step(g_resourses.target1.speed*directions_.x, g_resourses.target1.speed*directions_.y);
		setPosition(getPosition() + step);
	}

	target_c1* clone() const override {return new target_c1();}
	virtual ~target_c1() override {};
};


#endif //HELLO_SFML_TARGET_C1_HPP
