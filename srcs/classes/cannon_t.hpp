//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_CANNON_T_HPP
#define HELLO_SFML_CANNON_T_HPP
#include "interaction_objects.hpp"
#include "scope_t.hpp"

class cannon_t: public sf::Sprite {
private:
	scope_t									scope_;
public:
	cannon_t() {
		setTexture(g_resourses.cannon.texture);
		setScale(vector2f(g_resourses.cannon.texture_scale,g_resourses.cannon.texture_scale));
		setOrigin(g_resourses.cannon.origin);
		setPosition(g_win_width * HALF, g_win_height);
	}

	void	rotate_canon(const win_t& window) {
		scope_.set_scope_pos(window);
		setRotation(angele(scope_.getPosition(), getPosition()));
	}

	direction	top_dot() {
		vector2f	curent;
		auto			tex_y = static_cast<float>(getTexture()->getSize().y)*getScale().y;
		auto			rotation = static_cast<float>((getRotation() + 90.f)*RAD_TO_DEGREE);
		vector2f	r_cos_sin(cosf(rotation), sinf(rotation));

		curent = getPosition() - vector2f(tex_y*r_cos_sin.x, tex_y*r_cos_sin.y);
		return (direction(curent, r_cos_sin));
	}
	static cannon_t*						clone() 					{ return  new cannon_t(); }
	const scope_t&			getScope()	const {return scope_;}
	virtual ~cannon_t() {}
};


#endif //HELLO_SFML_CANNON_T_HPP
