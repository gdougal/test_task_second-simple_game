//
// Created by Gilberto Dougal on 4/24/21.
//

#ifndef HELLO_SFML_INTERACTION_HPP
#define HELLO_SFML_INTERACTION_HPP
#include "canonball_t.hpp"


class interaction {
public:
	interaction() = default;
	interaction(const interaction &ref) = default;
	interaction &operator=(const interaction &ref) = default;
	virtual ~interaction() = default;

	static const bool	co_orientation(interacion_obj& object1, interacion_obj& object2) {
		float	length_btwn_centre	= lenght(object1.getPosition(), object2.getPosition());
		float	length_in_move			= lenght(object1.getPosition() + object1.getDirections(), object2.getPosition() + object2.getDirections());
		return (length_btwn_centre >= length_in_move);
	}

	static const bool	is_collapse(interacion_obj& object1, interacion_obj& object2) {
		float	length_btwn_centre	= lenght(object1.getPosition(), object2.getPosition());
		float	sum_radius					= object1.getRadius() + object2.getRadius();
		return (length_btwn_centre <= sum_radius);
	}

	static void	collapse_targets(interacion_obj*& target1, interacion_obj*& target2) {
		if (&target1 == &target2)
			return;
		else if(co_orientation(*target1, *target2) && is_collapse(*target1, *target2)) {
			interacion_obj::swap_directions(target1, target2);
		}
	};

	static bool	collapse_target_with_ball(interacion_obj*& target, interacion_obj*& ball) {
		if(is_collapse(*target, *ball)) {
			target->minus_hp();
			interacion_obj::swap_directions(target, ball);
			return true;
		}
		return false;
	};
};


#endif //HELLO_SFML_INTERACTION_HPP
