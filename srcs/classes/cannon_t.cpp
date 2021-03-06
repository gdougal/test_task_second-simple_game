//
// Created by Gilberto Dougal on 4/23/21.
//

#include "cannon_t.hpp"


cannon_t::cannon_t(const t_resourses& res): scope_(new scope_t(res.getScope())) {
	setTexture(res.getCannon().getTexture());
	setScale(res.getCannon().getTextureScale(), res.getCannon().getTextureScale());
	setOrigin(res.getCannon().getOrigin());
	setPosition(res.getWinResourse().getWinWidth() * HALF, res.getWinResourse().getWinHeight());
}

void cannon_t::rotate_canon(const win_t &window) {
	scope_->set_scope_pos(window);
	setRotation(angele(scope_->getPosition(), getPosition()));
}

direction cannon_t::top_dot() {
	vector2f	curent;
	auto			tex_y = static_cast<float>(getTexture()->getSize().y)*getScale().y;
	auto			rotation = static_cast<float>((getRotation() + 90.f)*RAD_TO_DEGREE);
	vector2f	r_cos_sin(cosf(rotation), sinf(rotation));

	curent = getPosition() - vector2f(tex_y*r_cos_sin.x, tex_y*r_cos_sin.y);
	return (direction(curent, r_cos_sin));
}

const scope_t &cannon_t::getScope() const {return *scope_;}
