#pragma once
#include "I_AI.h"

class AI_Chase : public I_AI {
public:
	glm::vec3 target {0};
	float stoppage = 0.001;
	float speed = 0.001;

	AI_Chase(glm::vec3 target, float speed);
	~AI_Chase() = default;

	void update(GameObject& g) override;

	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};