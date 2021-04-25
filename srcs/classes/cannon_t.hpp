//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_CANNON_T_HPP
#define HELLO_SFML_CANNON_T_HPP
#include "interaction_objects.hpp"
#include "scope_t.hpp"

class cannon_t: public sf::Sprite {
public:
	cannon_t();
	~cannon_t() override = default;

	void						rotate_canon(const win_t& window);
	direction				top_dot();
	const scope_t&	getScope()	const;

//	static cannon_t*						clone() 					{ return  new cannon_t(); }
private:
	scope_t									scope_;
};


#endif //HELLO_SFML_CANNON_T_HPP
