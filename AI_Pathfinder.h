#pragma once
#include "I_AI.h"
#include "World.h"
#include "Pathfinding.h"

class AI_Pathfinder : public I_AI {
	bool path_found = false;
	bool path_complete = false;
public:
	World* world_ = nullptr;
	Pathfinding* path = nullptr;
	glm::vec3 target_ {0};
	float speed_ = 0.0f;

	AI_Pathfinder(World* world, glm::vec3 target, float speed);
	~AI_Pathfinder() = default;

	void update(GameObject& g) override;

	void generate_path(GameObject& g);
	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};