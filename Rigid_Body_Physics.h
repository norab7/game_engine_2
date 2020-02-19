#pragma once

#include "I_Physics.h"

class Rigid_Body_Physics : public I_Physics {
	glm::vec3 force {0.0f};
	float mass = 1.0f;
	float drag = 0.0f; // TODO: add drag, higher to make objects appear lighter
	float gravity = -9.81f;
	bool use_gravity = true;

public:
	Rigid_Body_Physics();
	~Rigid_Body_Physics() = default;

	// will take a world object eventually to update based on the current world environment
	void update(GameObject& g, int world_placeholder) override; 

	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};