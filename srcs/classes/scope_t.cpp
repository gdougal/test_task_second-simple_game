//
// Created by Gilberto Dougal on 4/22/21.
//

#include "scope_t.hpp"


scope_t::scope_t(const sprite_general &configure) {
	setTexture(configure.texture);
	setScale(configure.texture_scale, configure.texture_scale);
	setOrigin(configure.origin);
}

sf::Vector2<float> scope_t::get_pos_scope(const win_t &window) const {return static_cast<sf::Vector2<float> >(sf::Mouse::getPosition(window));}

void scope_t::set_scope_pos(const win_t &window) {setPosition(get_pos_scope(window));}
