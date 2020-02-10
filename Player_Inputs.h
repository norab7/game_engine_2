#pragma once
#include <memory>
#include <glfw3.h>

#include "I_Input.h"
#include "I_Component.h"

class Player_Inputs : public I_Input, I_Component {
	std::shared_ptr<bool[1024]> KEYS;

	float speed = 0.025f;

protected:
	void process_keyboard(GameObject& g) ;
	void process_mouse_movement(GameObject& g, double xpos, double ypos) ;
	void process_mouse_scroll(GameObject& g);

public:
	Player_Inputs(std::shared_ptr<bool[1024]> KEYS);
	~Player_Inputs() = default;

	void update(GameObject& g);
	void receive(int message);
};