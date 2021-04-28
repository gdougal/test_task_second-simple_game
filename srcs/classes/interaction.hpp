//
// Created by Gilberto Dougal on 4/24/21.
//

#ifndef HELLO_SFML_INTERACTION_HPP
#define HELLO_SFML_INTERACTION_HPP
#include "interaction_objects.hpp"
#include "target_c1.hpp"



class interaction {
public:
	interaction() = delete;
	interaction(const interaction &ref) = delete;
	interaction &operator=(const interaction &ref) = delete;
	virtual ~interaction() = delete;

	static void	collapse_targets(interacion_obj& target1, interacion_obj& target2);
	static bool	collapse_target_with_ball(interacion_obj& target, interacion_obj& ball, const t_resourses& res);
	static bool	collapse_target_with_bomb(interacion_obj& target, interacion_obj& bomb);
	static void	bomb_detonate(interacion_obj& target, interacion_obj& bomb, const t_resourses& res);

	static void	collaps_targets_with_board(interacion_obj& target, const sprite_balls& win) {
		if (target.getPosition().x <= win.getLeftBorder() || target.getPosition().x >= win.getRightBorder()) {
			target.inverse_x_dir();
		}
		if (target.getPosition().y <= win.getTopBorder() || target.getPosition().y >= win.getBotBorder()) {
			target.inverse_y_dir();
		}
	}

private:
	static bool	co_orientation(interacion_obj& object1, interacion_obj& object2);
	static bool	is_collapse(interacion_obj& object1, interacion_obj& object2);
};


#endif //HELLO_SFML_INTERACTION_HPP
