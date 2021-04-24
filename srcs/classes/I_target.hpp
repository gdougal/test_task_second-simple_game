//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_I_TARGET_HPP
#define HELLO_SFML_I_TARGET_HPP
#include "../shooting_range.hpp"

class I_target : public sf::Sprite {
protected:
	sf::Texture				target_texture_;
	int8_t					hp_;
	float					multiply_;
	float					radius_;
	vector2f				directions_;
	I_target				**swaped_;
public:
	virtual				~I_target() {};
	virtual void	target_move() = 0;
	virtual				I_target* clone() const = 0;
	void					swap_directions(I_target*& target1, I_target*& target2) { std::swap(target1->directions_, target2->directions_); }
	virtual void	collapse(I_target*& target1, I_target*& target2) {
		if (&target1 == &target2)
			return;
		if (lenght(target1->getPosition(), target2->getPosition()) > (target1->radius_ + target2->radius_)
			&& target1->swaped_ == &target2 && target2->swaped_ == &target1) {
			target1->swaped_ = nullptr;
			target2->swaped_ = nullptr;
		}
		if(lenght(target1->getPosition(), target2->getPosition()) <= (target1->radius_ + target2->radius_)) {
			if (target1->swaped_ != &target2 && target2->swaped_ != &target1)
			{
				swap_directions(target1, target2);
				target1->swaped_ = &target2;
				target2->swaped_ = &target1;
			}
//			target1->target_move();
//			target2->target_move();
		}
	};
	float					getRadius() const { return radius_; }
};


#endif //HELLO_SFML_I_TARGET_HPP
