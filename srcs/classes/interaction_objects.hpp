//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_INTERACTION_OBJECTS_HPP
#define HELLO_SFML_INTERACTION_OBJECTS_HPP
#include "../shooting_range.hpp"

class interacion_obj : public sf::Sprite {
public:
	interacion_obj() {};
	interacion_obj(const sprite_balls& config) {
		setTexture(config.getTexture());
		setScale(config.getTextureScale(), config.getTextureScale());
		setOrigin(config.getOrigin());
		radius_ = config.getRadius();
		hp_ = config.getHp();
		speed_ = config.getSpeed();
	}
	~interacion_obj() override = default;
	virtual void		move() = 0;
	virtual					interacion_obj* clone(const direction& pos_and_dir, const sprite_balls& config) const = 0;
	virtual void		set_start(const direction &startMv) = 0;

	static void			swap_directions(interacion_obj& target1, interacion_obj& target2) { std::swap(target1.directions_, target2.directions_); }
	float						getRadius()															const	{ return radius_; }
	const vector2f	&getDirections()												const	{ return directions_; }
	int							getHp()																	const	{ return hp_; }
	void						minus_hp()																		{ --hp_; }
	void						bomb_damage(const int damage)									{ hp_ = hp_ - damage; }
	bool						is_interactable() 											const { return interactable_; }
	void						setDirections(const vector2f &directions)			{ directions_ = directions; }
	void						inverse_y_dir() { directions_.y *= -1; }
	void						inverse_x_dir() { directions_.x *= -1; }

protected:
	bool				interactable_;
	vector2f		directions_;
	float				radius_;
	int					hp_;
	float				speed_;
};


#endif //HELLO_SFML_INTERACTION_OBJECTS_HPP
