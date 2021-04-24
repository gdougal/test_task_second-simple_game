//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_SCOPE_T_HPP
#define HELLO_SFML_SCOPE_T_HPP
#include "../shooting_range.hpp"


class	scope_t: public sf::Sprite {
private:
	sf::Texture				scope_texture_;
	static constexpr float	multiply_scale_ = 0.05;
public:
	scope_t() {
		if (!scope_texture_.loadFromFile(TEXTURE_SCOPE))
			throw(std::exception()); /// Is this right?
		setTexture(scope_texture_);
		setScale(sf::Vector2<float>(SCALE(multiply_scale_), SCALE(multiply_scale_)));
		setOrigin(static_cast<float>(getTexture()->getSize().x)/2, static_cast<float>(getTexture()->getSize().y)/2);
	}
	virtual ~scope_t() {}
	sf::Vector2<float>				get_pos_scope(const win_t& window)	{return static_cast<sf::Vector2<float> >(sf::Mouse::getPosition(window));}
	void							set_scope_pos(const win_t& window)	{setPosition(get_pos_scope(window));}
};


#endif //HELLO_SFML_SCOPE_T_HPP
