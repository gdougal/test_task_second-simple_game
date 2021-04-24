//
// Created by Gilberto Dougal on 4/25/21.
//

#ifndef HELLO_SFML_BOMB_HPP
#define HELLO_SFML_BOMB_HPP
#include "interaction_objects.hpp"

class bomb: public interacion_obj {
private:
	float			height_;
	vector2f	booom_dot_;
	float			length_;
public:
	bomb() = default;
	explicit	bomb(const direction &startMv) {
		radius_ = g_resourses.cannonball.radius;
		setTexture(g_resourses.cannonball.texture);
		setScale(vector2f (g_resourses.cannonball.texture_scale, g_resourses.cannonball.texture_scale));
		setOrigin(g_resourses.cannonball.origin);
		setPosition(startMv.first);
		directions_ = startMv.second;
		hp_ = 0;
		height_ = 0;
		booom_dot_ = static_cast<vector2f>(sf::Mouse::getPosition());
		length_ = lenght(getPosition(), booom_dot_);
	}

	auto 	scale_factor(const float way) const {
		float	popravka = way <= length_ / 2.f ? length_ : 0;
		float factor = abs(popravka - length_/(way > 0.01 ? way : length_));
		return vector2f(factor, factor);
	}

	void	move() override {
		if (getPosition() != booom_dot_) {
			vector2f a(g_resourses.cannonball.speed * getDirections().x, g_resourses.cannonball.speed * getDirections().y);
			setPosition(getPosition() - a);
		}
		setScale(scale_factor(lenght(getPosition(), booom_dot_)));
	}

	bomb* clone(const direction &pos_and_dir) const override { return new bomb(pos_and_dir); }

	virtual ~bomb() {}
};


#endif //HELLO_SFML_BOMB_HPP
