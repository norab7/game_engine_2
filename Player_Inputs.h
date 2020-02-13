#pragma once
#include <memory>

#include "I_Input.h"

class Player_Inputs : public I_Input {
	const bool *key_map;
	const std::pair<float, float>* mouse_offset;
	float speed = 0.025f;

protected:

public:
	Player_Inputs(const bool(&KEY_MAP)[1024], const std::pair<float,float>& mouse);
	~Player_Inputs() = default;

	void update(GameObject& g) override;
	void receive(int message) override;

	void process_keyboard(GameObject& g) override;
	void process_mouse_movement(GameObject& g) override;
	void process_mouse_scroll(GameObject& g)override;
};