//
// Created by Gilberto Dougal on 4/24/21.
//

#ifndef HELLO_SFML_TARGET_C2_HPP
#define HELLO_SFML_TARGET_C2_HPP
#include "interaction_objects.hpp"

class target_c2: public interacion_obj {
public:
	target_c2();
	~target_c2() override = default;
	void				move() override;
	target_c2*	clone(const direction& pos_and_dir) const override;

private:
	void				set_start(const direction &startMv) override;
};


#endif //HELLO_SFML_TARGET_C2_HPP
