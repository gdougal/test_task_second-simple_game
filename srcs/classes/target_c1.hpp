//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_TARGET_C1_HPP
#define HELLO_SFML_TARGET_C1_HPP
#include "I_target.hpp"


class target_c1: public I_target {
	static constexpr float	multiply_scale_ = 0.05f;
public:
	target_c1() {
		if (!target_texture_.loadFromFile(TEXTURE_TARGET1))
			throw(std::exception());
		setTexture(target_texture_);
		setScale(sf::Vector2<float>(SCALE(multiply_scale_), SCALE(multiply_scale_)));
		setOrigin(static_cast<float>(getTexture()->getSize().x) / 2.f, static_cast<float>(getTexture()->getSize().y) / 2.f);
		radius_ = static_cast<float>(getTexture()->getSize().x) * getScale().x * 0.5f;
		setPosition(random_float(radius_, g_win_width - radius_), random_float(radius_, g_win_height * 0.7f));
		directions_ = normalize(getPosition(), vector2f(random_float(0, g_win_width), random_float(0, g_win_width)));
		multiply_ = 100.f;
	};
	target_c1(const target_c1 &ref) = default;
	target_c1 &operator=(const target_c1 &ref) = default;

	virtual void target_move() override {
		if (getPosition().x <= radius_ || getPosition().x >= g_win_width - radius_) {
			directions_.x *= -1;
		}
		if (getPosition().y <= radius_ || getPosition().y >= g_win_height*0.7f) {
			directions_.y *= -1;
		}
		vector2f a(TARGET_SPEED(multiply_)*directions_.x, TARGET_SPEED(multiply_)*directions_.y);
		setPosition(getPosition() + a);
	}

//	virtual void	collapse(I_target*& target1, I_target*& target2) override {
//		if (&target1 == &target2)
//			return;
//		if(lenght(target1->getPosition(), target2->getPosition()) <= 2*radius_) {
//			swap_directions(target1, target2);
//			target1->target_move();
//			target2->target_move();
//		}
//	}

	target_c1* clone() const override {return new target_c1;}
	virtual ~target_c1() override {};
};


#endif //HELLO_SFML_TARGET_C1_HPP
