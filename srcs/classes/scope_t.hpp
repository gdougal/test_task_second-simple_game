//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_SCOPE_T_HPP
#define HELLO_SFML_SCOPE_T_HPP
#include "interaction_objects.hpp"


class	scope_t: public sf::Sprite {
public:
	scope_t() {
		setTexture(g_resourses.scope.texture);
		setScale(g_resourses.scope.texture_scale, g_resourses.scope.texture_scale);
		setOrigin(g_resourses.scope.origin);
	}
	virtual ~scope_t() {}
	const sf::Vector2<float>	get_pos_scope(const win_t& window)	const {return static_cast<sf::Vector2<float> >(sf::Mouse::getPosition(window));}
	void											set_scope_pos(const win_t& window)	{setPosition(get_pos_scope(window));}
};


#endif //HELLO_SFML_SCOPE_T_HPP
