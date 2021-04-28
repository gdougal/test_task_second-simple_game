//
// Created by Gilberto Dougal on 4/24/21.
//

#include "interaction.hpp"

bool interaction::collapse_target_with_ball(interacion_obj& target, interacion_obj& ball, const t_resourses& res) {
	if(is_collapse(target, ball)) {
		interacion_obj::swap_directions(target, ball);
		target.setDirections(vector2f(target.getDirections().x * -1, target.getDirections().y * -1));
		target.minus_hp(res.getManagment()->getStandardDamage());
		return true;
	}
	return false;
}

bool interaction::collapse_target_with_bomb(interacion_obj& target, interacion_obj& bomb) {
	if(bomb.is_interactable() && is_collapse(target, bomb)) {
		return true;
	}
	return false;
}

void interaction::collapse_targets(interacion_obj& target1, interacion_obj& target2) {
	if(co_orientation(target1, target2) && is_collapse(target1, target2)) {
		interacion_obj::swap_directions(target1, target2);
	}
}

void interaction::bomb_detonate(interacion_obj& target, interacion_obj& bomb, const t_resourses& res) {
	float	sum_radius = target.getRadius() + bomb.getRadius() * res.getWinResourse().getMultiplyBoomRadius();
	if(lenght_(target.getPosition(), bomb.getPosition()) < sum_radius) {
		target.bomb_damage(res.getManagment()->getBombDamage());
		res.getManagment()->addScoreBomb();
	}
}


bool	interaction::co_orientation(interacion_obj &object1, interacion_obj &object2) {
	float	length_btwn_centre	= lenght_(object1.getPosition(), object2.getPosition());
	float	length_in_move			= lenght_(object1.getPosition() + object1.getDirections(), object2.getPosition() + object2.getDirections());
	return (length_btwn_centre >= length_in_move);
}

bool	interaction::is_collapse(interacion_obj &object1, interacion_obj &object2) {
	float	length_btwn_centre	= lenght_(object1.getPosition(), object2.getPosition());
	float	sum_radius					= object1.getRadius() + object2.getRadius();
	return (length_btwn_centre <= sum_radius);
}


