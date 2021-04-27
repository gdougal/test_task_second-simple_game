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
public:

	logic(const std::string& config_path);
	logic() = delete;
	~logic() = default;

	void		update_game_logic();
	void		draw_game_objects();
	void		shooting();
	void		bomb_shooting();

	void		stop() {

	}

	const t_resourses &getResourses() const;

	void setSessionWindow(sf::RenderWindow *sessionWindow);

private:
	void	generate_targets(int number, const sprite_balls& target_conf);
	void	moving_cannonballs();
	void	moving_targets();
	void	collapse_targets();
	void	collapse_cannonbals();
	template	<class T_Container>
	void draw_cycle(T_Container& pool) {
		for (auto& item: pool) {
			session_window->draw(*item);
		}
	}


	typedef	std::shared_ptr<interacion_obj>	ptr_interact;
	typedef	std::list<ptr_interact>					t_balls_lst;
	typedef	std::list<ptr_interact>					t_target_lst;
	sf::RenderWindow												*session_window;
	std::shared_ptr<cannon_t>								cannon_;
	t_balls_lst															balls_;
	t_target_lst														targets_;
	t_resourses															resourses_;
};


#endif //HELLO_SFML_LOGIC_HPP
