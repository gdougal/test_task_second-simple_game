//
// Created by Gilberto Dougal on 4/25/21.
//

#include "bomb.hpp"

bomb::bomb() {
	radius_ = g_resourses.bomb.radius;
	setTexture(g_resourses.bomb.texture);
	setScale(g_resourses.bomb.texture_scale, g_resourses.bomb.texture_scale);
	setOrigin(g_resourses.bomb.origin);
	hp_ = 0;
	start_scale_ = getScale().y;
	interactable_ = false;
	speed_ = start_speed_ = g_resourses.bomb.speed;
}

void bomb::move() {
	float way = lenght_(start_pos_, getPosition());
	if (way <= length_) {
		float scale_f =  scale_factor(way);
		scale_f = scale_f > 1 ? scale_f : 1;
		setScale(vector2f(start_scale_ * scale_f, start_scale_ * scale_f));
		speed_ = start_speed_/(scale_f*HALF);
		vector2f a(speed_ * getDirections().x, speed_ * getDirections().y);
		setPosition(getPosition() - a);
	}
	else {
		interactable_ = true;
	}
}

bomb *bomb::clone(const direction &pos_and_dir) const {
	auto bomb_n = new bomb();
	return bomb_n;
}



float bomb::scale_factor(const float way) const {
	float factor = a_*powf(way, 2) + b_*way + c_;
	return abs(factor);
}

bomb *bomb::clone_fo_bomb(const direction &pos_and_dir, const vector2f &bomb_dot) {
	auto bomb_n = clone(pos_and_dir);
	bomb_n->set_start(pos_and_dir);
	bomb_n->start_pos_ = pos_and_dir.first;
	bomb_n->booom_dot_ = bomb_dot;
	bomb_n->length_ = lenght_(bomb_n->start_pos_, bomb_n->booom_dot_);
	bomb_n->a_ = (-4.f) / powf(bomb_n->length_, 2);
	bomb_n->b_ = 4.f/bomb_n->length_;
	bomb_n->c_ = 1;
	return bomb_n;
}

void bomb::set_start(const direction &startMv) {
	setPosition(startMv.first);
	directions_ = startMv.second;
}
