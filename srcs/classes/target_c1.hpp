//
// Created by Gilberto Dougal on 4/23/21.
//

#ifndef HELLO_SFML_TARGET_C1_HPP
#define HELLO_SFML_TARGET_C1_HPP
#include "interaction_objects.hpp"


class target_c1: public interacion_obj {
public:
	target_c1();
	~target_c1() override = default;

	void					move() override;
	target_c1*		clone(const direction& pos_and_dir) const override;

private:
	void					set_start(const direction &startMv) override;
};


#endif //HELLO_SFML_TARGET_C1_HPP
