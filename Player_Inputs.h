#pragma once
#include <memory>

#include "I_Input.h"
#include "I_Component.h"

class Player_Inputs : public I_Input, I_Component {
	std::shared_ptr<bool[1024]> KEYS;

	float speed = 0.025f;

protected:

public:
	Player_Inputs();
	~Player_Inputs() = default;

	void update(GameObject& g) override;
	void receive(int message);

	//void process_keyboard(GameObject g) override;
	//void process_mouse_movement(GameObject g, double xpos, double ypos) override;
	//void process_mouse_scroll(GameObject g)override;
};