#pragma once
#include "I_Emitter.h"

class PE_Explosion : public I_Emitter {
	I_Graphics* graphics_ = nullptr;
	I_Physics* physics_ = nullptr;
	
	float created_time;

	float life_span;
	unsigned active_max;
	float velocity_offset = 1.0f;

	glm::vec3 velocity {0};

	std::vector<GameObject*> particles;

public:
	PE_Explosion(glm::vec3 position, I_Graphics* graphics, I_Physics* physics, glm::vec3 velocity, float life, unsigned count, float v_offset = 2.0f);
	~PE_Explosion() = default;

	void update(GameObject& g) override;
	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};