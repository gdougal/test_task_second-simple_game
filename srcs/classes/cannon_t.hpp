//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_CANNON_T_HPP
#define HELLO_SFML_CANNON_T_HPP
#include "../shooting_range.hpp"
#include "scope_t.hpp"

class cannon_t: public sf::Sprite {
private:
	scope_t			scope_;
	sf::Texture		cannon_texture_;
	static constexpr float	multiply_scale_ = 0.2f;
public:
	cannon_t() {
		if (!cannon_texture_.loadFromFile(TEXTURE_CANNON))
			throw(std::exception()); /// Is this right?
		setTexture(cannon_texture_);
		setScale(vector2f(SCALE(multiply_scale_),SCALE(multiply_scale_)));
		setOrigin(static_cast<float>(getTexture()->getSize().x)/2.f, static_cast<float>(getTexture()->getSize().y));
		setPosition(g_win_width/2.f, g_win_height);
	}

	void	rotate_canon(const win_t& window) {
		scope_.set_scope_pos(window);
		setRotation(angele(scope_.getPosition(), getPosition()));
	}

	direction	top_dot() {
		vector2f	curent;
		auto			tex_y = static_cast<float>(cannon_texture_.getSize().y)*getScale().y;
		auto			rotation = static_cast<float>((getRotation() + 90.f)*RAD_TO_DEGREE);
		vector2f	r_cos_sin(cosf(rotation), sinf(rotation));

		curent = getPosition() - vector2f(tex_y*r_cos_sin.x, tex_y*r_cos_sin.y);
		return (direction(curent, r_cos_sin));
	}
	const scope_t&			getScope()	const {return scope_;}
	virtual ~cannon_t() {}
};


#endif //HELLO_SFML_CANNON_T_HPP
