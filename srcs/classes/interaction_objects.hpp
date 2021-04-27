//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_INTERACTION_OBJECTS_HPP
#define HELLO_SFML_INTERACTION_OBJECTS_HPP
#include "../shooting_range.hpp"

class interacion_obj : public sf::Sprite {
public:
	interacion_obj(const sprite_balls& config) {
		setTexture(config.texture);
		setScale(config.texture_scale, config.texture_scale);
		setOrigin(config.origin);
		radius_ = config.radius;
		hp_ = config.hp;
		speed_ = config.speed;
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
	void						death_small_target()													{ hp_ = hp_ - g_resourses.target1.hp; }
	bool						is_interactable() 											const { return interactable_; }
	void						setDirections(const vector2f &directions)			{ directions_ = directions; }

protected:
	bool				interactable_;
	vector2f		directions_;
	float				radius_;
	int					hp_;
	float				speed_;
};


#endif //HELLO_SFML_INTERACTION_OBJECTS_HPP
