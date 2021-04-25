//
// Created by Gilberto Dougal on 4/25/21.
//

#ifndef HELLO_SFML_LOGIC_HPP
#define HELLO_SFML_LOGIC_HPP
#include "wrap_window.hpp"
#include "cannon_t.hpp"
#include "target_c2.hpp"
#include "interaction.hpp"
#include "target_c1.hpp"
#include "canonball_t.hpp"
#include "bomb.hpp"
#include <list>
#include "gui.hpp"


class	logic {
public:

	logic() = delete;
	logic(sf::RenderWindow *pubWindow);
	~logic() = default;
	void		setPubWindow(sf::RenderWindow *pubWindow);

	void		update_game_logic();
	void		draw_game_objects();
	void		shooting();
	void		bomb_shooting();

	void		stop() {

	}

private:
	void	generate_targets();
	void	moving_cannonballs();
	void	moving_targets();
	void	collapse_targets();
	void	collapse_cannonbals();
	void	draw_cannonballs();
	void	draw_targets();


	typedef	std::shared_ptr<interacion_obj>	ptr_interact;
	typedef	std::list<ptr_interact>					t_balls_lst;
	typedef	std::list<ptr_interact>					t_target_lst;
	sf::RenderWindow												*session_window;
	cannon_t																cannon_;
	t_balls_lst															balls_;
	t_target_lst														targets_;
};


#endif //HELLO_SFML_LOGIC_HPP
