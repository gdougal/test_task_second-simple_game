//
// Created by Gilberto Dougal on 4/24/21.
//

#ifndef HELLO_SFML_INTERACTION_HPP
#define HELLO_SFML_INTERACTION_HPP
#include "interaction_objects.hpp"

typedef	std::shared_ptr<interacion_obj>	ptr_interact;


class interaction {
public:
	interaction() = delete;
	interaction(const interaction &ref) = delete;
	interaction &operator=(const interaction &ref) = delete;
	virtual ~interaction() = delete;

	static void	collapse_targets(ptr_interact& target1, ptr_interact& target2);
	static bool	collapse_target_with_ball(ptr_interact& target, ptr_interact& ball);
	static bool	collapse_target_with_bomb(ptr_interact& target, ptr_interact& bomb);
	static void	bomb_detonate(ptr_interact& target, ptr_interact& bomb);

private:
	static int score_;

	static int	getScore() { return score_; }
	static void	setScore(int counter) { interaction::score_ = counter; }
	static const bool	co_orientation(interacion_obj& object1, interacion_obj& object2);
	static const bool	is_collapse(interacion_obj& object1, interacion_obj& object2);
};


#endif //HELLO_SFML_INTERACTION_HPP
