//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_INTERACTION_OBJECTS_HPP
#define HELLO_SFML_INTERACTION_OBJECTS_HPP
#include "../shooting_range.hpp"

class interacion_obj : public sf::Sprite {
protected:
	float				radius_;
	vector2f		directions_;
	int8_t			hp_;
public:
	virtual					~interacion_obj() {};
	virtual void		move() = 0;
	virtual					interacion_obj* clone() const = 0;
	static void			swap_directions(interacion_obj*& target1, interacion_obj*& target2) { std::swap(target1->directions_, target2->directions_); }

	void						setDirections(const vector2f &directions)			{ directions_ = directions; }
	float						getRadius()															const	{ return radius_; }
	const vector2f	&getDirections()												const	{ return directions_; }
	int8_t					getHp()																	const	{ return hp_; }
	void minus_hp()	{ --hp_; }

};


#endif //HELLO_SFML_INTERACTION_OBJECTS_HPP
