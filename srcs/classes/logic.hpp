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

	void							handler_key(int key) {
		if (key == sf::Keyboard::Escape) {
			managment_->ChangeGameMode();
			if (managment_->isGameMode() == PAUSE) {
				managment_->fillPauseStart();
				session_window->setMouseCursorGrabbed(false);
				session_window->setMouseCursorVisible(true);
			}
			else {
				managment_->fillPauseEnd();
				session_window->setMouseCursorGrabbed(resourses_->getWinResourse().isMouseCursorGrabbed());
				session_window->setMouseCursorVisible(resourses_->getWinResourse().isMouseCursorVisible());
			}
			return;
		}
		switch (managment_->isGameMode()) {
			case GAME:
				handler_concreet_key(key);
			case PAUSE:
				break;
		}
	}

	void						game_actions() {
		session_window->clear();
		if (managment_->isRoundEnd()) {
			restart_game();
		}
		switch (managment_->isGameMode()) {
			case GAME:
				update_game_logic();
				draw_game_objects();
				break;
			case PAUSE:
				draw_game_objects();
				break;
		}
		session_window->display();
	}

private:
	void restart_game() {
		managment_->AddAllCorrectionTime();
		managment_->relosdScore();
//		managment_->ChangeBombInplace();
		session_window->clear();
		targets_.clear();
		generate_all_targets();
	};


	void							handler_concreet_key(int key) {
		switch (key) {
			case sf::Keyboard::Q:
				shooting();
				break;
			case sf::Keyboard::W:
				if (!managment_->isBombInplace()) {
					bomb_shooting();
					managment_->ChangeBombInplace();
				}
				break;
			case sf::Keyboard::R:
				restart_game();
				break;
		}
	}
	void	generate_targets(int number, const sprite_balls& target_conf);
	void	generate_all_targets() {
		generate_targets(resourses_->getWinResourse().getSmallYellowNum(), resourses_->getTargetSmallYellow());
		generate_targets(resourses_->getWinResourse().getBigGreenNum(), resourses_->getTargetBigGreen());
	}

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
