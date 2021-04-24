//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_I_TARGET_HPP
#define HELLO_SFML_I_TARGET_HPP
#include "../shooting_range.hpp"

class I_target : public sf::Sprite {
protected:
	sf::Texture	target_texture_;
	int8_t			hp_;
	float				multiply_;
	float				radius_;
	vector2f		directions_;
public:
	virtual					~I_target() {};
	virtual void		move() = 0;
	virtual					I_target* clone() const = 0;
	static void			swap_directions(I_target*& target1, I_target*& target2) { std::swap(target1->directions_, target2->directions_); }

	void						setDirections(const vector2f &directions)			{ directions_ = directions; }
	float						getRadius()															const	{ return radius_; }
	const vector2f	&getDirections()												const	{ return directions_; }
	int8_t					getHp()																	const	{ return hp_; }
	void minus_hp()	{ --hp_; }

};


#endif //HELLO_SFML_I_TARGET_HPP
