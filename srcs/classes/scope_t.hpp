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
	~scope_t() override = default;
	sf::Vector2<float>				get_pos_scope(const win_t& window)	const;
	void											set_scope_pos(const win_t& window);
};


#endif //HELLO_SFML_SCOPE_T_HPP
