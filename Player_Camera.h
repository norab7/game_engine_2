#pragma once

#include "I_Camera.h"

class Player_Camera : public I_Camera {
	const std::pair<float, float>* mouse_offset;
	bool has_target = false;
	float yaw = -90.0f;
	float pitch = 0.0f;

	float lastX = 0.0f;
	float lastY = 0.0f;

public:
	Player_Camera(const std::pair<float, float>& offset);
	~Player_Camera() = default;

	void update(GameObject& g) override;

	void receive(std::string component, std::string action) override;
	void activate() override;
	void deactivate() override;
};