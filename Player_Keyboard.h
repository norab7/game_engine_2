#pragma once
#include <memory>

#include "I_Input.h"

class Player_Keyboard : public I_Input {
	const bool* key_map;
	float speed = 2.5f;
	float modifier = 5.0f;

protected:

public:
	Player_Keyboard(const bool(&KEY_MAP)[1024]);
	~Player_Keyboard() = default;

	void update(GameObject& g) override;

	void receive(std::string component, std::string action) override;
	void activate() override;
	void deactivate() override;
};