#pragma once

#include "I_Physics.h"

class Rigid_Body_Physics : public I_Physics {
	glm::vec3 gravity {0, -9.81f, 0};
	bool use_gravity = true;
	float time = 0.0f;

public:
	Rigid_Body_Physics();
	~Rigid_Body_Physics() = default;

	// will take a world object eventually to update based on the current world environment
	void update(GameObject& g, int world_placeholder) override;

	void receive(std::string component, std::string action) override;
	void activate() override;
	void deactivate() override;
};