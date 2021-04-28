//
// Created by Gilberto Dougal on 4/25/21.
//

#include "logic.hpp"



logic::logic(const std::string& config_path): resourses_(new t_resourses(Config(config_path))) {
	std::shared_ptr<cannon_t> tmp(cannon_t::clone(*resourses_));
	cannon_.swap(tmp);
	generate_all_targets();
	managment_ = resourses_->getManagment();
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
	session_window->draw(*managment_->getScoreText());
	session_window->draw(*managment_->getTimeText());
}

void logic::shooting() {
	balls_.emplace_back(false, cannonball_t().clone(cannon_->top_dot(), resourses_->getCannonball()));
}

void logic::bomb_shooting() {
	if  (cannon_->getScope().get_pos_scope(*session_window).y < resourses_->getBomb().getBotBorder()) {
		balls_.emplace_back(false, bomb().clone_fo_bomb(cannon_->top_dot(), cannon_->getScope().get_pos_scope(*session_window), resourses_->getBomb()));
	}
}

void logic::generate_targets(int number, const sprite_balls& target_conf) {
	for (int i = 0; i < number; ++i) {
		targets_.emplace_back(false, target_c1().clone(random_pos_dir_generator(*resourses_), target_conf));
	}
}

void logic::moving_cannonballs() {
	for (auto & ball : balls_) {
		(ball.second)->move();
		if ((ball.second)->getPosition().x < 0 || ball.second->getPosition().y < 0 || ball.second->getPosition().x > resourses_->getWinResourse().getWinWidth()
						|| ball.second->getPosition().y > resourses_->getWinResourse().getWinHeight())
		{
			ball.first =  true;
			if (is_object<interacion_obj, bomb>(ball.second.get()))
				managment_->ChangeBombInplace();
		}
	}
}

void logic::moving_targets() {
	for (auto & target : targets_) {
		interaction::collaps_targets_with_board(*(target.second.get()), resourses_->getTargetSmallYellow());
		target.second->move();
	}
}

void logic::collapse_targets() {
	for (auto& target_1 : targets_) {
		for (auto& target_2 : targets_) {
			interaction::collapse_targets(*target_1.second, *target_2.second);
		}
	}
}


void logic::collapse_cannonbals() {
	for (auto& it: balls_) {
		for (auto& it_t : targets_) {
			if (!it_t.first && is_object<interacion_obj, cannonball_t>(it.second.get()) && interaction::collapse_target_with_ball(*it_t.second, *it.second, *resourses_)) {
				if (it_t.second->getHp() <= 0) {
					it_t.first =  true;
				}
				managment_->addScoreStandard();
				it.first = true;
				break;
			}
			if (is_object<interacion_obj, bomb>(it.second.get()) && interaction::collapse_target_with_bomb(*it_t.second, *it.second)) {
	it.second->setTexture(resourses_->getBomb().getExploseText()); /// it`s boom texture;
				for (auto& it_bomb_zone : targets_) {
					interaction::bomb_detonate(*it_bomb_zone.second, *it.second, *resourses_);
					if (it_bomb_zone.second->getHp() <= 0) {
						it_bomb_zone.first = true;
					}
				}
				it.first = true;
				managment_->ChangeBombInplace();
				break;
			}
		}
	}
}

void logic::draw_cycle(logic::t_interact_lst &pool) {
	for (auto& item: pool) {
		session_window->draw(*item.second);
	}
}

void logic::delete_cycle(t_interact_lst& pool) {
	for (auto iter = pool.begin(); iter != pool.end(); ) {
		if (iter->first)
			iter = pool.erase(iter);
		else
			++iter;
	}
}

const t_resourses	&logic::getResourses()																		const { return *resourses_; }
void							logic::setSessionWindow(sf::RenderWindow *sessionWindow)				{ session_window = sessionWindow; }
