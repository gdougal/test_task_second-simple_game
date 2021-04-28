//
// Created by Gilberto Dougal on 4/25/21.
//

#ifndef HELLO_SFML_LOGIC_HPP
#define HELLO_SFML_LOGIC_HPP
#include "wrap_window.hpp"
#include "cannon_t.hpp"
#include "interaction.hpp"
#include "target_c1.hpp"
#include "canonball_t.hpp"
#include "bomb.hpp"
#include <list>

class	logic {
	typedef	std::shared_ptr<interacion_obj>											ptr_interact;
	typedef	std::list<std::pair<bool, ptr_interact> >						t_interact_lst;
public:

	logic(const std::string& config_path);
	logic() = delete;
	~logic() = default;
	void							update_game_logic();
	void							draw_game_objects();
	void							shooting();
	void							bomb_shooting();
	const t_resourses &getResourses() const;
	void 							setSessionWindow(sf::RenderWindow *sessionWindow);
	void							handler_key(int key);
	void							game_actions();

private:
	void restart_game();
	void	handler_concreet_key(int key);
	void	generate_targets(int number, const sprite_balls& target_conf);
	void	generate_all_targets();
	void	moving_cannonballs();
	void	moving_targets();
	void	collapse_targets();
	void	collapse_cannonbals();
	void	delete_cycle(t_interact_lst& pool);
	void	draw_cycle(t_interact_lst& pool);

	sf::RenderWindow*							session_window;
	std::shared_ptr<cannon_t>			cannon_;
	t_interact_lst								balls_;
	t_interact_lst								targets_;
	std::shared_ptr<t_resourses>	resourses_;
	std::shared_ptr<t_managment>	managment_;
};


#endif //HELLO_SFML_LOGIC_HPP
