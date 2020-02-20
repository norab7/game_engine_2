#pragma once
#include "I_Emitter.h"

class PE_Explosion : public I_Emitter {
	I_Graphics* graphics_ = nullptr;
	I_Physics* physics_ = nullptr;
	
	float created_time;

	float life_span = 10;
	unsigned active_max = 10;
	bool explosion = false;
	float spawn_rate = 1.0f;
	float velocity_offset = 1.0f;

	bool first_run = true;

	glm::vec3 velocity {0};

	std::vector<GameObject*> particles;

public:
	PE_Explosion(I_Graphics* graphics, I_Physics* physics, glm::vec3 velocity, float life, unsigned count, float v_offset = 2.0f);
	~PE_Explosion() = default;

	void update(GameObject& g) override;
	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};