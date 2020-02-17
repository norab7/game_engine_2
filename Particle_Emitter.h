#pragma once
#include "I_Emitter.h"

class Particle_Emitter : public I_Emitter {
	I_Graphics* graphics_ = nullptr;
	I_Physics* physics_ = nullptr;
	
	unsigned life_span = 250;
	unsigned active_max = 10;
	bool explosion = false;
	float spawn_rate = 1.0f;
	float velocity_offset = 1.0f;

	bool first_run = true;

	glm::vec3 velocity {0};

	std::vector<GameObject*> particles;

public:
	Particle_Emitter(I_Graphics* graphics, I_Physics* physics, glm::vec3 velocity, unsigned life, unsigned count, bool burst = false, float rate = 1.0f, float v_offset = 2.0f);
	~Particle_Emitter() = default;

	void update(GameObject& g) override;
	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};