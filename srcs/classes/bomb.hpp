//
// Created by Gilberto Dougal on 4/25/21.
//

#ifndef HELLO_SFML_BOMB_HPP
#define HELLO_SFML_BOMB_HPP
#include "interaction_objects.hpp"

class bomb: public interacion_obj {
public:
	bomb() {};
	explicit bomb(const sprite_balls& config);
	void	move() override;
	bomb*	clone_fo_bomb(const direction &pos_and_dir, const vector2f& bomb_dot, const sprite_balls& config);
	~bomb() override = default;

private:
	float			start_scale_;
	float			start_speed_;
	vector2f	booom_dot_;
	vector2f	start_pos_;
	float			length_;
	float			a_;
	float			b_;
	float			c_;
	float			scale_factor(float way) const;
	bomb*			clone(const direction &pos_and_dir, const sprite_balls& config) const override;
	void			set_start(const direction &startMv) override;
};


#endif //HELLO_SFML_BOMB_HPP
