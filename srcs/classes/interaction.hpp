//
// Created by Gilberto Dougal on 4/24/21.
//

#ifndef HELLO_SFML_INTERACTION_HPP
#define HELLO_SFML_INTERACTION_HPP
#include "interaction_objects.hpp"


class interaction {
public:
	interaction() = default;
	interaction(const interaction &ref) = default;
	interaction &operator=(const interaction &ref) = default;
	virtual ~interaction() = default;

	static const bool	co_orientation(interacion_obj& object1, interacion_obj& object2) {
		float	length_btwn_centre	= lenght_(object1.getPosition(), object2.getPosition());
		float	length_in_move			= lenght_(object1.getPosition() + object1.getDirections(), object2.getPosition() + object2.getDirections());
		return (length_btwn_centre >= length_in_move);
	}

	static const bool	is_collapse(interacion_obj& object1, interacion_obj& object2) {
		float	length_btwn_centre	= lenght_(object1.getPosition(), object2.getPosition());
		float	sum_radius					= object1.getRadius() + object2.getRadius();
		return (length_btwn_centre <= sum_radius);
	}

	static void	collapse_targets(std::shared_ptr<interacion_obj>& target1, std::shared_ptr<interacion_obj>& target2) {
		 if(co_orientation(*target1, *target2) && is_collapse(*target1, *target2)) {
			interacion_obj::swap_directions(*target1, *target2);
		}
	};

	static bool	collapse_target_with_ball(std::shared_ptr<interacion_obj>& target, std::shared_ptr<interacion_obj>& ball) {
		if(is_collapse(*target, *ball)) {
			interacion_obj::swap_directions(*target, *ball);
			(*target).setDirections(vector2f(target->getDirections().x * -1, target->getDirections().y * -1));
			target->minus_hp();
			return true;
		}
		return false;
	};

	static bool	collapse_target_with_bomb(std::shared_ptr<interacion_obj>& target, std::shared_ptr<interacion_obj>& bomb) {
		if(bomb->is_interactable() && is_collapse(*target, *bomb)) {
			return true;
		}
		return false;
	};

	static void	bomb_detonate(std::shared_ptr<interacion_obj>& target, std::shared_ptr<interacion_obj>& bomb) {
		float	sum_radius = target->getRadius() + bomb->getRadius() * MULTIPLU_BOMB_RADIUS;
		if(lenght_(target->getPosition(), bomb->getPosition()) < sum_radius)
			target->death_small_target();
	};
};


#endif //HELLO_SFML_INTERACTION_HPP
