//
// Created by Gilberto Dougal on 4/22/21.
//

#ifndef HELLO_SFML_CANONBALL_T_HPP
#define HELLO_SFML_CANONBALL_T_HPP
#include "interaction_objects.hpp"

class	cannonball_t: public interacion_obj {
public:
	cannonball_t() {};
	explicit cannonball_t(const sprite_balls& config);
	~cannonball_t() override = default;
	
	void					move() override;
	cannonball_t*	clone(const direction &pos_and_dir, const sprite_balls& config) const override;

private:
	void					set_start(const direction &startMv) override;
};

#endif //HELLO_SFML_CANONBALL_T_HPP
