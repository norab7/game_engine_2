#pragma once
#include <memory>

#include "I_Input.h"

class Player_Inputs : public I_Input {
	bool *key_map;

	float speed = 0.025f;

protected:

public:
	Player_Inputs(bool(&KEY_MAP)[1024]);
	~Player_Inputs() = default;

	void update(GameObject& g) override;
	void receive(int message) override;

	void process_keyboard(GameObject& g) override;
	void process_mouse_movement(GameObject& g, double xpos, double ypos) override;
	void process_mouse_scroll(GameObject& g)override;
};