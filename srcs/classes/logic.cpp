//
// Created by Gilberto Dougal on 4/25/21.
//

#include "logic.hpp"



logic::logic(const std::string& config_path): resourses_(new t_resourses(Config(config_path))) {
	std::shared_ptr<cannon_t> tmp(cannon_t::clone(*resourses_));
	cannon_.swap(tmp);
	generate_targets(resourses_->getWinResourse().getSmallYellowNum(), resourses_->getTargetSmallYellow());
	generate_targets(resourses_->getWinResourse().getBigGreenNum(), resourses_->getTargetBigGreen());
	bomb_inplace = false;
}

void logic::update_game_logic() {
	delete_cycle(targets_);
	delete_cycle(balls_);
	cannon_->rotate_canon(*session_window);
	collapse_cannonbals();
	collapse_targets();
	moving_cannonballs();
	moving_targets();
}

void logic::draw_game_objects() {
	draw_cycle(targets_);
	session_window->draw(*cannon_);
	draw_cycle(balls_);
	session_window->draw(cannon_->getScope());
}

void logic::shooting() {
	balls_.emplace_back(cannonball_t().clone(cannon_->top_dot(), resourses_->getCannonball()));
}

void logic::bomb_shooting() {
	if  (cannon_->getScope().get_pos_scope(*session_window).y < resourses_->getBomb().getBotBorder() && !bomb_inplace) {
		balls_.emplace_back(bomb().clone_fo_bomb(cannon_->top_dot(), cannon_->getScope().get_pos_scope(*session_window), resourses_->getBomb()));
			bomb_inplace = true;
		}
}

void logic::generate_targets(int number, const sprite_balls& target_conf) {
	for (int i = 0; i < number; ++i) {
		targets_.emplace_back(target_c1().clone(random_pos_dir_generator(*resourses_), target_conf));
	}
}

void logic::moving_cannonballs() {
	for (auto it = balls_.begin(); it != balls_.end(); ++it) {
		(*it)->move();
		if ((*it)->getPosition().x < 0 || (*it)->getPosition().y < 0 || (*it)->getPosition().x > resourses_->getWinResourse().getWinWidth()
						|| (*it)->getPosition().y > resourses_->getWinResourse().getWinHeight())
		{
			del_obj.emplace_back(it);
			if (is_object<interacion_obj, bomb>(it->get()))
				bomb_inplace = false;
		}
	}
}

void logic::moving_targets() {
	for (auto it = targets_.begin(); it != targets_.end(); ++it) {
		interaction::collaps_targets_with_board(*(it->get()), resourses_->getTargetSmallYellow());
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

	for (auto it = balls_.begin(); it != balls_.end(); ++it) {
		for (auto it_t = targets_.begin(); it_t != targets_.end(); ++it_t) {
			if (is_object<interacion_obj, cannonball_t>(it->get()) && interaction::collapse_target_with_ball(*it_t, *it)) {
				if ((*it_t)->getHp() <= 0) {
					del_obj.emplace_back(it_t);
				}
				del_obj.emplace_back(it);
				break;
			}
			if (is_object<interacion_obj, bomb>(it->get()) && interaction::collapse_target_with_bomb(*it_t, *it)) {
				(*it)->setTexture(resourses_->getBomb().getExploseText());
				for (auto it_bomb_zone = targets_.begin(); it_bomb_zone != targets_.end(); ++it_bomb_zone) {
					interaction::bomb_detonate(*it_bomb_zone, *it, *resourses_);
					if ((*it_bomb_zone)->getHp() <= 0) {
						del_obj.emplace_back(it_bomb_zone);
						bomb_inplace = false;
					}
				}
				it_t = targets_.begin();
				del_obj.emplace_back(it);
				break;
			}
		}
	}
}

void logic::delete_cycle(std::list<ptr_interact> &pool) {
	del_obj.unique();
	for (auto& iter: del_obj) {
		pool.erase(iter);
	}
	del_obj.clear();
}

const t_resourses &logic::getResourses() const { return *resourses_; }
void logic::setSessionWindow(sf::RenderWindow *sessionWindow) { session_window = sessionWindow; }
