//
// Created by Gilberto Dougal on 4/25/21.
//

#include "logic.hpp"



logic::logic(sf::RenderWindow *pubWindow) {
	generate_targets();
	session_window = pubWindow;
}

void logic::setPubWindow(sf::RenderWindow *pubWindow) { session_window = pubWindow; }

void logic::update_game_logic() {
	cannon_.rotate_canon(*session_window);
	collapse_cannonbals();
	collapse_targets();
	moving_cannonballs();
	moving_targets();
}

void logic::draw_game_objects() {
	draw_targets();
	session_window->draw(cannon_);
	draw_cannonballs();
	session_window->draw(cannon_.getScope());
}

void logic::shooting() {
	balls_.emplace_back(cannonball_t().clone(cannon_.top_dot()));
}

void logic::bomb_shooting() {
	if  (cannon_.getScope().get_pos_scope(*session_window).y < g_resourses.target1.bot_border)
		balls_.emplace_back(bomb().clone_fo_bomb(cannon_.top_dot(), cannon_.getScope().get_pos_scope(*session_window)));
}

void logic::generate_targets() {
	for (int i = 0; i < g_targets_small_num; ++i) {
		targets_.emplace_back(target_c1().clone(random_pos_dir_generator()));
	}
	for (int i = 0; i < g_targets_big_num; ++i) {
		targets_.emplace_back(target_c2().clone(random_pos_dir_generator()));
	}
}

void logic::moving_cannonballs() {
	for (auto it = balls_.begin(); it != balls_.end(); ) {
		(*it)->move();
		if ((*it)->getPosition().x < 0 || (*it)->getPosition().y < 0 ||
				(*it)->getPosition().x > g_win_width || (*it)->getPosition().y > g_win_height) {
			balls_.erase(it++);
		}
		else
			++it;
	}
}

void logic::moving_targets() {
	for (auto it = targets_.begin(); it != targets_.end(); ++it) {
		(*it)->move();
	}
}

void logic::collapse_targets() {
	for (auto it = targets_.begin(); it != targets_.end(); ++it) {
		for (auto it_i = it; it_i != targets_.end(); ++it_i) {
			interaction::collapse_targets(*it, *it_i);
		}
	}
}


void logic::collapse_cannonbals() {
	std::vector<std::list<interacion_obj>::iterator>	for_del;

	for (auto it = balls_.begin(); !balls_.empty() && it != balls_.end(); ++it) {
		for (auto it_t = targets_.begin(); !targets_.empty() && it_t != targets_.end(); ++it_t) {
			if (is_object<interacion_obj, cannonball_t>(it->get()) && interaction::collapse_target_with_ball(*it_t, *it)) {
				if ((*it_t)->getHp() <= 0) {
					it_t = targets_.erase(it_t);
				}
				it = balls_.erase(it);
				if (balls_.empty() || it == balls_.end() || !is_object<interacion_obj, cannonball_t>(it->get()))
					break;
			}
			if (is_object<interacion_obj, bomb>(it->get()) && interaction::collapse_target_with_bomb(*it_t, *it)) {
				for (auto it_bomb_zone = targets_.begin(); !targets_.empty() && it_bomb_zone != targets_.end(); ++it_bomb_zone) {
					interaction::bomb_detonate(*it_bomb_zone, *it);
					if ((*it_bomb_zone)->getHp() <= 0) {
						it_bomb_zone = targets_.erase(it_bomb_zone);
					}
				}
				it_t = targets_.begin();
				it = balls_.erase(it);
				if (balls_.empty() || it == balls_.end() || !is_object<interacion_obj, cannonball_t>(it->get()))
					break;
			}
		}
	}
}

void logic::draw_cannonballs() {
	for (auto& i: balls_) {
		session_window->draw(*i);
	}
}

void logic::draw_targets() {
	for (auto& i: targets_) {
		session_window->draw(*i);
	}
}
