//
// Created by Gilberto Dougal on 4/24/21.
//

#ifndef HELLO_SFML_TARGET_C2_HPP
#define HELLO_SFML_TARGET_C2_HPP
#include "I_target.hpp"

class target_c2: public I_target {
private:
	static constexpr float	multiply_scale_ = 0.075f;
public:
	target_c2() {
		if (!target_texture_.loadFromFile(TEXTURE_TARGET2))
			throw(std::exception());
		setTexture(target_texture_);
		setScale(vector2f(SCALE(multiply_scale_), SCALE(multiply_scale_)));
		setOrigin(static_cast<float>(getTexture()->getSize().x) / 2, static_cast<float>(getTexture()->getSize().y) / 2);
		radius_ = static_cast<float>(getTexture()->getSize().x) * getScale().x * 0.5f;
		setPosition(random_float(radius_, g_win_width - radius_), random_float(radius_, g_win_height * 0.7f - radius_));
		directions_ = normalize(getPosition(), vector2f(random_float(0, g_win_width), random_float(0, g_win_width)));
		multiply_ = 120.f;
		swaped_ = nullptr;
	};
	target_c2(const target_c2 &ref) = default;
	target_c2 &operator=(const target_c2 &ref) = default;

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
//
//	}
	target_c2* clone() const override {return new target_c2;}
	virtual ~target_c2() override {};
};


#endif //HELLO_SFML_TARGET_C2_HPP
