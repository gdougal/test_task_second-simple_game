//
// Created by Gilberto Dougal on 4/24/21.
//

#include "interaction.hpp"

bool interaction::collapse_target_with_ball(ptr_interact &target, ptr_interact &ball) {
	if(is_collapse(*target, *ball)) {
		interacion_obj::swap_directions(*target, *ball);
		(*target).setDirections(vector2f(target->getDirections().x * -1, target->getDirections().y * -1));
		target->minus_hp();
		return true;
	}
	return false;
}

bool interaction::collapse_target_with_bomb(ptr_interact &target, ptr_interact &bomb) {
	if(bomb->is_interactable() && is_collapse(*target, *bomb)) {
		return true;
	}
	return false;
}

void interaction::collapse_targets(ptr_interact& target1, ptr_interact& target2) {
	if(co_orientation(*target1, *target2) && is_collapse(*target1, *target2)) {
		interacion_obj::swap_directions(*target1, *target2);
	}
}

void interaction::bomb_detonate(ptr_interact &target, ptr_interact &bomb) {
	float	sum_radius = target->getRadius() + bomb->getRadius() * MULTIPLU_BOMB_RADIUS;
	if(lenght_(target->getPosition(), bomb->getPosition()) < sum_radius) {
		target->bomb_damage(target->getHp());
	}
}


const bool	interaction::co_orientation(interacion_obj &object1, interacion_obj &object2) {
	float	length_btwn_centre	= lenght_(object1.getPosition(), object2.getPosition());
	float	length_in_move			= lenght_(object1.getPosition() + object1.getDirections(), object2.getPosition() + object2.getDirections());
	return (length_btwn_centre >= length_in_move);
}

const bool	interaction::is_collapse(interacion_obj &object1, interacion_obj &object2) {
	float	length_btwn_centre	= lenght_(object1.getPosition(), object2.getPosition());
	float	sum_radius					= object1.getRadius() + object2.getRadius();
	return (length_btwn_centre <= sum_radius);
}


